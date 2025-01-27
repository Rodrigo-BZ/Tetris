/**
 * @file GameWindow.cpp
 * @brief This file implements the functions for the GameWindow class
 * @version 0.1
 * 
 */
#include "GameWindow.h"
#include "./ui_GameWindow.h"

void GameWindow::focusInEvent(QFocusEvent *event) {
    setFocus();
    QMainWindow::focusInEvent(event);
}

/**
 * @brief Construct a new Game Window:: Game Window object and connect all signals from PlayerClient object to appropriate functions.
 * 
 * @param parent 
 */
GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow), m_playerClient(std::make_unique<PlayerClient>(this))
{
    ui->setupUi(this);

    connect(m_playerClient.get(), &PlayerClient::connected, this, &GameWindow::connectedToServer);
    connect(m_playerClient.get(), &PlayerClient::loggedIn, this, &GameWindow::loggedIn);
    connect(m_playerClient.get(), &PlayerClient::loginError, this, &GameWindow::loginFailed);
    connect(m_playerClient.get(), &PlayerClient::messageReceived, this, &GameWindow::messageReceived);
    connect(m_playerClient.get(), &PlayerClient::disconnected, this, &GameWindow::disconnectedFromServer);
    connect(m_playerClient.get(), &PlayerClient::error, this, &GameWindow::error);
    connect(m_playerClient.get(), &PlayerClient::userJoined, this, &GameWindow::userJoined);
    connect(m_playerClient.get(), &PlayerClient::userLeft, this, &GameWindow::userLeft);

    setFocus();
}

/**
 * @brief This function sets the value of the multip boolean and follows with appropriate measures.
 * 
 * @param multip Boolean value that indicates if the current game is singleplayer or multiplayer.
 */
void GameWindow::SetMultiPlayer(bool multip)
{
    this->multip = multip;

    ResetUi(multip);

    if(multip) {
        ui->btnReset->hide();
        ui->btnMenu->setGeometry((width() - 84) / 2, 180, 84, 30);
        ui->btnConnect->show();
    }
    else {
        ui->btnReset->show();
        ui->btnMenu->setGeometry(10, 10, 84, 30);
        ui->btnConnect->hide();

        InitializeGame();
    }
}

/**
 * @brief This function does everything necessary to initialize a new game.
 * 
 */
void GameWindow::InitializeGame()
{
    ResetUi(multip);

    if(multip) {
        gameOverLabel->setStyleSheet("font-size: 32px; color: red; font-weight: bold;");
        gameOverLabel->setAlignment(Qt::AlignCenter);
        gameOverLabel->setGeometry(75, (height() - 100) / 2, 300, 100);
        gameOverLabel->hide();

        opponentGameOverLabel->setStyleSheet("font-size: 32px; color: red; font-weight: bold;");
        opponentGameOverLabel->setAlignment(Qt::AlignCenter);
        opponentGameOverLabel->setGeometry(width() - 300 - 75, (height() - 100) / 2, 300, 100);
        opponentGameOverLabel->hide();

        waitingOpponentLabel->hide();
        playerNameLabel->show();
        opponentNameLabel->show();
        opponentGrid->Show();
    }
    else {
        gameOverLabel->setStyleSheet("font-size: 32px; color: red; font-weight: bold;");
        gameOverLabel->setAlignment(Qt::AlignCenter);
        gameOverLabel->setGeometry((width() - 300) / 2, (height() - 100) / 2, 300, 100);
        gameOverLabel->hide();
        scoreLabel->show();
    }

    Niveau = 0;
    linesCleared = 0;
    Score = 0;
    blocPosition[0] = 3;
    blocPosition[1] = 0;

    UpdateScoreLabel();
    PredictBloc();
    GenerateBloc();

    grid->Show();
    predLabel->show();
    levelLabel->show();

    timer = std::make_unique<QTimer>(this);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->setInterval(600);
    timer->start();

    allowMovements = true;
}

/**
 * @brief This function initializes the prediction QLabel and NextBlocPred objects.
 * 
 * @param labelStartingX The starting X position for displaying the label.
 * @param blocStartingX The starting X position for displaying the bloc.
 */
void GameWindow::InitializePredictionWidget(int labelStartingX, int blocStartingX)
{
    predLabel = std::make_unique<QLabel>("NEXT BLOC", this);
    predLabel->setGeometry(labelStartingX, 270, 200, 30);
    predLabel->setFont(QFont("8514oem"));
    predLabel->setStyleSheet("font-size: 16px; color: white;");
    predLabel->setAlignment(Qt::AlignCenter);
    predLabel->hide();
    blocPred = std::make_unique<NextBlocPred>(this, blocStartingX, 300, 30, 30);
}

/**
 * @brief This function initializes the score and level Qlabel's.
 * 
 * @param startingX The starting X position for both labels.
 */
void GameWindow::InitializeScoreWidget(int startingX)
{
    scoreLabel = std::make_unique<QLabel>("Score: 0", this);
    scoreLabel->setFont(QFont("8514oem"));
    scoreLabel->setGeometry(startingX, 110, 200, 30);
    scoreLabel->setStyleSheet("font-size: 22px; color: white;");
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->hide();

    levelLabel = std::make_unique<QLabel>("Level: 0", this);
    levelLabel->setFont(QFont("8514oem"));
    levelLabel->setGeometry(startingX, 140, 200, 30);
    levelLabel->setStyleSheet("font-size: 22px; color: white;");
    levelLabel->setAlignment(Qt::AlignCenter);
    levelLabel->hide();
}

/**
 * @brief This function updates the score and level QLabel's with the current values of score an level of the game.
 * 
 */
void GameWindow::UpdateScoreLabel() {
    scoreLabel->setText("Score: " + QString::number(Score));
    levelLabel->setText("Level: " + QString::number(Niveau));
}

GameWindow::~GameWindow()
{
    delete ui;
}

/**
 * @brief This function sets the value of the pointer to the menu window object.
 * 
 * @param menuWindow Pointer to an object of the class MenuWindow.
 */
void GameWindow::GetMenuWindowPtr(QWidget *menuWindow)
{
    this->menuWindow = menuWindow;
}

/**
 * @brief This function resets all visual elements in the game window.
 * 
 * @param multip Boolean value that indicates if the current game is singleplayer or multiplayer.
 */
void GameWindow::ResetUi(bool multip)
{
    if(multip) {
        grid = std::make_unique<GameGrid>(this, 75, 50, 30, 30);

        InitializePredictionWidget((width() - 200) / 2, (width() - 100) / 2);
        InitializeScoreWidget((width() - 200) / 2);
    }
    else {
        grid = std::make_unique<GameGrid>(this, (width() - 300) / 2, (height() - 630) / 2, 30, 30);

        InitializePredictionWidget(width() - 300, width() - 250);
        InitializeScoreWidget(width() - 300);
    }

    opponentGrid = std::make_unique<GameGrid>(this, width() - 300 - 75, 50, 30, 30);
    opponentGameOverLabel = std::make_unique<QLabel>("GAME OVER", this);
    opponentGameOverLabel->hide();
    waitingOpponentLabel = std::make_unique<QLabel>("Waiting for opponent to connect...", this);
    waitingOpponentLabel->setStyleSheet("font-size: 15px; color: white;");
    waitingOpponentLabel->setAlignment(Qt::AlignCenter);
    waitingOpponentLabel->setGeometry((width() - 400) / 2, 200, 400, 100);
    waitingOpponentLabel->hide();

    if(playerNameLabel != nullptr)
        playerNameLabel->hide();
    if(opponentNameLabel != nullptr)
        opponentNameLabel->hide();

    gameOverLabel = std::make_unique<QLabel>("GAME OVER", this);
    gameOverLabel->hide();
}

/**
 * @brief This function is activated on the click of the menu button. It stops the game, disconnects from server and leaves to menu window.
 * 
 */
void GameWindow::on_btnMenu_clicked()
{
    if(timer != nullptr)
        timer->stop();
    allowMovements = false;

    if(multip)
        m_playerClient->disconnectFromHost();

    menuWindow->show();
    this->close();
}

/**
 * @brief This function is activated on the click of the reset button. It resets the current game.
 * 
 */
void GameWindow::on_btnReset_clicked()
{
    ResetUi(multip);
    InitializeGame();
}

/**
 * @brief This function is activated on the click of the connect button. It calls the attemptConnection() function.
 * 
 */
void GameWindow::on_btnConnect_clicked()
{
    attemptConnection();
}

/**
 * @brief This function generates a new Bloc object and stores it in the nextBloc attribute.
 * 
 */
void GameWindow::PredictBloc()
{
    int blocType = rand() % 7;
    switch(blocType) {
    case 0:
        nextBloc = std::make_shared<BlocL>();
        break;
    case 1:
        nextBloc = std::make_shared<BlocI>();
        break;
    case 2:
        nextBloc = std::make_shared<BlocO>();
        break;
    case 3:
        nextBloc = std::make_shared<BlocT>();
        break;
    case 4:
        nextBloc = std::make_shared<BlocJ>();
        break;
    case 5:
        nextBloc = std::make_shared<BlocS>();
        break;
    case 6:
        nextBloc = std::make_shared<BlocZ>();
        break;
    }
    blocPred->SetNextBloc(nextBloc->GetForme(),nextBloc->GetColor());
}

/**
 * @brief This function generates a new Bloc.
 * 
 */
void GameWindow::GenerateBloc()
{
    currentBloc = nextBloc;
    PredictBloc();
    PlaceBloc();
    setFocus();
}

/**
 * @brief This function places a Bloc on the grid.
 * 
 */
void GameWindow::PlaceBloc()
{
    if(!grid->ColorGrid(currentBloc->GetForme(), blocPosition, blocPosition, currentBloc->GetColor(),DOWN)) {
        gameOver();
        if(multip)
            sendMessage('l');
    }

    if(multip)
        sendMessage(' ');
}

/**
 * @brief This function is used for updating the Bloc's position.
 * 
 * @param difference Int vector that representes the Bloc's dislocation in both directions.
 * @param direction The direction of the BLoc's movement.
 */
void GameWindow::UpdateBlocPosition(int *difference, Direction direction)
{
    int initialPosition[2] = {blocPosition[0], blocPosition[1]};
    blocPosition[0] += difference[0];
    blocPosition[1] += difference[1];

    if (!grid->ColorGrid(currentBloc->GetForme(), blocPosition, initialPosition, currentBloc->GetColor(), direction)) {
        if (difference[0] == 0 && difference[1] == 1) {
            if(blocPosition[1] < 3){
                gameOver();
            }
            FixBloc();
        } else {
            blocPosition[0] = initialPosition[0];
            blocPosition[1] = initialPosition[1];
        }
    }

    if(multip)
        sendMessage(' ');
}

/**
 * @brief This function fixates the Bloc in it's place and handles appropriate measures after.
 * 
 */
void GameWindow::FixBloc()
{
    linesClearedatOnce = 0;
    for(int j = 0; j < 21;j++){
        ExcludeLine(j);
    }
    switch(linesClearedatOnce) {
        case 0:
            break;
        case 1:
            Score += 40 * (Niveau + 1);
            UpdateScoreLabel();
            break;
        case 2:
            if(multip) {
                sendMessage('p');
                sendMessage(' ');
            }
            Score += 100 * (Niveau + 1);
            UpdateScoreLabel();
            break;
        case 3:
            if(multip) {
                sendMessage('p');
                sendMessage('p');
                sendMessage(' ');
            }
            Score += 300 * (Niveau + 1);
            UpdateScoreLabel();
            break;
        case 4:
            if(multip) {
                sendMessage('p');
                sendMessage('p');
                sendMessage('p');
                sendMessage('p');
                sendMessage(' ');
            }
            Score += 1200 * (Niveau + 1);
            UpdateScoreLabel();
            break;
    }
    blocPosition[0] = 3;
    blocPosition[1] = 0;
    GenerateBloc();
}

/**
 * @brief This function ends the game, displaying the current player's loss.
 * 
 */
void GameWindow::gameOver()
{
    timer->stop();
    allowMovements = false;

    gameOverLabel->show();
    gameOverLabel->raise();

    if(multip) {
        opponentGameOverLabel->setText("VICTORY");
        opponentGameOverLabel->setStyleSheet("font-size: 32px; color: green; font-weight: bold;");
        opponentGameOverLabel->show();
        sendMessage('l');
    }
}

/**
 * @brief This function ends the game, displaying the current player's victory.
 * 
 */
void GameWindow::Victory()
{
    opponentGameOverLabel->show();
    opponentGameOverLabel->raise();

    timer->stop();
    allowMovements = false;

    gameOverLabel->setText("VICTORY");
    gameOverLabel->setStyleSheet("font-size: 32px; color: green; font-weight: bold;");
    gameOverLabel->show();
}

/**
 * @brief This function is called each time the timer is activated. It moves the current Bloc down by 1 cell in the grid.
 * 
 */
void GameWindow::TimerEvent()
{
    int difference[2] = {0, 1};
    UpdateBlocPosition(difference, DOWN);
}

/**
 * @brief This function is called when the player presses a key on the keyboard. It handles the possible movements.
 * 
 * @param k 
 */
void GameWindow::keyPressEvent(QKeyEvent *k)
{
    if(allowMovements) {
        int diff_left[2] = {-1,0};
        int diff_right[2] = {1,0};
        int diff_down[2] = {0,1};
        int double_diff_right[2] = {2,0};
        int double_diff_left[2] = {-2,0};

        switch (k -> key()) {
            case Qt::Key_Left:
                UpdateBlocPosition(diff_left, LEFT);
                break;
            case Qt::Key_Right:
                UpdateBlocPosition(diff_right, RIGHT);
                break;
            case Qt::Key_Down:
                UpdateBlocPosition(diff_down, DOWN);
                break;
            case Qt::Key_Space:
                for(int i = 1; i < 21; i++){
                    int inPosition[2] = {blocPosition[0], blocPosition[1]+i-1};
                    int afPosition[2] = {blocPosition[0], blocPosition[1]+i};
                    if(!grid->ColorGrid(currentBloc->GetForme(), afPosition, inPosition, currentBloc->GetColor(), DOWN)){
                        FixBloc();
                        break;
                    }
                }
                break;
            case Qt::Key_Z:
                if(currentBloc -> GetLenght() == 4){
                    break;
                }
                if(blocPosition[0] < 0){
                    switch(blocPosition[0]){
                    case -1:
                        UpdateBlocPosition(diff_right, RIGHT);
                        break;
                    case -2:
                        UpdateBlocPosition(double_diff_right, RIGHT);
                        break;
                    }
                }
                else if(blocPosition[0] > 6){
                    switch(blocPosition[0]){
                    case 8:
                        if(currentBloc -> GetLenght() == 16){
                            UpdateBlocPosition(double_diff_left, LEFT);
                        }
                        else{
                            UpdateBlocPosition(diff_left, LEFT);
                        }
                        break;
                    case 9:
                        UpdateBlocPosition(double_diff_left, LEFT);
                        break;
                    }
                }
                currentBloc->RotateClockwise(blocPosition, grid.get());
                break;
            case Qt::Key_X:
                if(currentBloc -> GetLenght() == 4){
                    break;
                }
                if(blocPosition[0] < 0){
                    switch(blocPosition[0]){
                    case -1:
                        UpdateBlocPosition(diff_right, RIGHT);
                        break;
                    case -2:
                        UpdateBlocPosition(double_diff_right, RIGHT);
                        break;
                    }
                }
                else if(blocPosition[0] > 7){
                    switch(blocPosition[0]){
                    case 8:
                        if(currentBloc -> GetLenght() == 16){
                            UpdateBlocPosition(double_diff_left, LEFT);
                        }
                        UpdateBlocPosition(diff_left, LEFT);
                        break;
                    case 9:
                        UpdateBlocPosition(double_diff_left, LEFT);
                        break;
                    }
                }
                currentBloc->RotateCounterClockwise(blocPosition, grid.get());
                break;
        }
    }
}

/**
 * @brief This function excludes a line from the game grid.
 * 
 * @param LineNumber The line to be excluded.
 */
void GameWindow::ExcludeLine(int LineNumber)
{
    int k = 0;

    for (int i = 0; i < 10; i++) {
        if (((grid->GetLabelGrid())[i][LineNumber]->palette()).color(QPalette::Window) != Qt::gray) {
            k += 1;
        }
    }

    if (k == 10) {
        linesClearedatOnce += 1;
        for (int i = 0; i < 10; i++) {
            for (int j = LineNumber; j > 0; j--) {
                (grid->GetLabelGrid())[i][j]->setPalette(
                    (grid->GetLabelGrid())[i][j - 1]->palette()
                );
            }
        }
        for (int i = 0; i < 10; i++) {
            (grid->GetLabelGrid())[i][0]->setPalette(Qt::gray);
        }
        linesCleared+=1;
        if(linesCleared>=10){
            Niveau+=1;
            UpdateScoreLabel();
            timer->setInterval(600 - Niveau * 50);
            linesCleared=0;
        }
        if(multip)
            sendMessage(' ');
    }
}

/**
 * @brief This functions adds a line as a penalty for the current player.
 * 
 */
void GameWindow::AddLinePenalty()
{
    grid->AddLineBottom(currentBloc->GetForme(), blocPosition);
}

/**
 * @brief This function connects the player to the server at the desired address.
 * 
 */
void GameWindow::attemptConnection()
{
    // We use 127.0.0.1 (localhost)
    QString hostAddress = "127.0.0.1";
    // Tell the client to connect to the host using the port 7777
    m_playerClient->connectToServer(QHostAddress(hostAddress), 7777);
}

/**
 * @brief This function is called when the player is connected to server. It pops up a prompt asking for the player's username.
 * 
 */
void GameWindow::connectedToServer()
{
    // once we connected to the server we ask the user for what username they would like to use
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"));
    if (newUsername.isEmpty()){
        // if the user clicked cancel or typed nothing, we just disconnect from the server
        QMessageBox::warning(this, tr("Invalid Username"), tr("Empty username"));
        return m_playerClient->disconnectFromHost();
    }
    // try to login with the given username
    attemptLogin(newUsername);
}

/**
 * @brief This function attempts to login the player with the given username.
 * 
 * @param userName QString that holds the desired username.
 */
void GameWindow::attemptLogin(const QString &userName)
{
    // use the client to attempt a log in with the given username
    m_playerClient->login(userName);
    playerName = userName;
}

/**
 * @brief This function is called when the player is succesfully logged in. It handles visual changes.
 * 
 */
void GameWindow::loggedIn()
{
    // once we successfully log in we enable the ui to display and send messages
    ui->btnConnect->hide();

    waitingOpponentLabel->show();

    playerNameLabel = std::make_unique<QLabel>(playerName, this);
    playerNameLabel->setStyleSheet("font-size: 30px; color: white;");
    playerNameLabel->setAlignment(Qt::AlignCenter);
    playerNameLabel->setGeometry(75, 0, 300, 50);
    playerNameLabel->hide();
}

/**
 * @brief This function is called when the login failed. It displays an error message and tries to connect the user again.
 * 
 * @param reason 
 */
void GameWindow::loginFailed(const QString &reason)
{
    // the server rejected the login attempt
    // display the reason for the rejection in a message box
    QMessageBox::critical(this, tr("Error"), reason);
    // allow the user to retry, execute the same slot as when just connected
    connectedToServer();
}

/**
 * @brief This function is called when the player receives a message from the server. It handles the consequences for each message.
 * 
 * @param sender QSrtring containing the username of the message's sender.
 * @param text QSrtring containing the message's content.
 */
void GameWindow::messageReceived(const QString &sender, const QString &text)
{
    if(text.compare(QLatin1String("start"), Qt::CaseInsensitive) == 0) {
        opponentNameLabel = std::make_unique<QLabel>(sender, this);
        opponentNameLabel->setStyleSheet("font-size: 30px; color: white;");
        opponentNameLabel->setAlignment(Qt::AlignCenter);
        opponentNameLabel->setGeometry(width() - 300 - 75, 0, 300, 50);
        opponentNameLabel->hide();

        InitializeGame();
    }
    else if(text.compare(QLatin1String("over"), Qt::CaseInsensitive) == 0) {
        Victory();
    }
    else if(text.compare(QLatin1String("penalty"), Qt::CaseInsensitive) == 0)
        AddLinePenalty();
    else
        opponentGrid->CopyState(text);
}

/**
 * @brief This function sends a message that will be broadcasted by the server.
 * 
 * @param event QChar that contains a letter if there is a specific event to transmit. Is empty space if just for tranferring grid state.
 */
void GameWindow::sendMessage(QChar event)
{
    QString message;

    if(event == 's') // Start game
        message = "start";
    else if(event == 'l') // Game over
        message = "over";
    else if(event == 'p') // Penalty
        message = "penalty";
    else // No event
        message = grid->SaveState();

    // we use the client to send the message
    m_playerClient->sendMessage(message);
}

/**
 * @brief This function is called when the player is disconneted from the server. It emits a warning message and stops the game.
 * 
 */
void GameWindow::disconnectedFromServer()
{
    if(timer != nullptr)
        timer->stop();
    on_btnMenu_clicked();

    // if the client loses connection to the server
    // communicate the event to the user via a message box
    QMessageBox::warning(this, tr("Disconnected"), tr("You have been disconnected"));
}

/**
 * @brief This function is called when another user joins the server. It starts the game.
 * 
 * @param username QString containing the username of the player that joined the server.
 */
void GameWindow::userJoined(const QString &username)
{
    opponentNameLabel = std::make_unique<QLabel>(username, this);
    opponentNameLabel->setStyleSheet("font-size: 30px; color: white;");
    opponentNameLabel->setAlignment(Qt::AlignCenter);
    opponentNameLabel->setGeometry(width() - 300 - 75, 0, 300, 50);
    opponentNameLabel->hide();

    sendMessage('s');
    InitializeGame();
}

/**
 * @brief This function is called when another user leaves the server. It ends the game if it hasn't already ended.
 * 
 * @param username QString containing the username of the player that left the server. 
 */
void GameWindow::userLeft(const QString &username)
{
    if(gameOverLabel->isHidden()) {
        Victory();
    }

    waitingOpponentLabel->show();

    QMessageBox::information(this, tr("User Left"), tr("%1 Left").arg(username));
}

/**
 * @brief This function handles possible errors in server communications.
 * 
 * @param socketError The error received.
 */
void GameWindow::error(QAbstractSocket::SocketError socketError)
{
    // show a message to the user that informs of what kind of error occurred
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return; // handled by disconnectedFromServer
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occurred"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy communication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
}
