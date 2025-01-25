#include "GameWindow.h"
#include "./ui_GameWindow.h"

void GameWindow::focusInEvent(QFocusEvent *event) {
    setFocus();
    QMainWindow::focusInEvent(event);
}

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow), m_playerClient(new PlayerClient(this))
{
    ui->setupUi(this);

    InitializeScoreWidget();

    predLabel = new QLabel("Next bloc:", this);
    predLabel->setGeometry(width() - 220, 230, 200, 30);
    predLabel->setStyleSheet("font-size: 16px; color: black;");

    predLabel->show();
    blocPred = new NextBlocPred(this, width() - 200, 270, 20, 20);

    connect(m_playerClient, &PlayerClient::connected, this, &GameWindow::connectedToServer);
    connect(m_playerClient, &PlayerClient::loggedIn, this, &GameWindow::loggedIn);
    connect(m_playerClient, &PlayerClient::loginError, this, &GameWindow::loginFailed);
    connect(m_playerClient, &PlayerClient::messageReceived, this, &GameWindow::messageReceived);
    connect(m_playerClient, &PlayerClient::disconnected, this, &GameWindow::disconnectedFromServer);
    connect(m_playerClient, &PlayerClient::error, this, &GameWindow::error);
    connect(m_playerClient, &PlayerClient::userJoined, this, &GameWindow::userJoined);
    connect(m_playerClient, &PlayerClient::userLeft, this, &GameWindow::userLeft);

    setFocus();
}

void GameWindow::SetMultiPlayer(bool multip)
{
    this->multip = multip;
    if(multip) {
        attemptConnection();
    }
    else {
        InitializeGame();
    }
}

void GameWindow::InitializeGame()
{
    if(multip) {
        grid = new GameGrid(this, 75, 30, 30, 30);
        opponentGrid = new GameGrid(this, 425, 30, 30, 30);

        ui->btnReset->hide();

        gameOverLabel = new QLabel("GAME OVER", this);
        gameOverLabel->setStyleSheet("font-size: 32px; color: red; font-weight: bold;");
        gameOverLabel->setAlignment(Qt::AlignCenter);
        int x = (width() / 4) - 125;
        int y = (height() - 100) / 2;
        gameOverLabel->setGeometry(x, y, 300, 100);
        gameOverLabel->hide();

        opponentGameOverLabel = new QLabel("GAME OVER", this);
        opponentGameOverLabel->setStyleSheet("font-size: 32px; color: red; font-weight: bold;");
        opponentGameOverLabel->setAlignment(Qt::AlignCenter);
        int oppx = ((width() * 3) / 4) - 175;
        int oppy = (height() - 100) / 2;
        opponentGameOverLabel->setGeometry(oppx, oppy, 300, 100);
        opponentGameOverLabel->hide();
    }
    else {
        grid = new GameGrid(this, 250, 30, 30, 30);

        ui->btnReset->show();

        gameOverLabel = new QLabel("GAME OVER", this);
        gameOverLabel->setStyleSheet("font-size: 32px; color: red; font-weight: bold;");
        gameOverLabel->setAlignment(Qt::AlignCenter);
        int x = (width() - 300) / 2;
        int y = (height() - 100) / 2;
        gameOverLabel->setGeometry(x, y, 300, 100);
        gameOverLabel->hide();
    }

    Niveau = 0;
    linesCleared = 0;
    Score = 0;
    blocPosition[0] = 3;
    blocPosition[1] = 0;
    PredictBloc();
    GenerateBloc();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->setInterval(600);
    timer->start();
}

void GameWindow::InitializeScoreWidget() {
    scoreLabel = new QLabel("Score: 0", this);

    scoreLabel->setGeometry(width() - 220, 80, 200, 30);
    scoreLabel->setStyleSheet("font-size: 22px; color: black;");

    scoreLabel->show();

    levelLabel = new QLabel("Level: 0", this);

    levelLabel->setGeometry(width()-220, 120, 200, 30);
    levelLabel->setStyleSheet("font-size: 22px; color: black;");

    levelLabel->show();
}

void GameWindow::UpdateScoreLabel() {
    scoreLabel->setText("Score: " + QString::number(Score));
    levelLabel->setText("Level: " + QString::number(Niveau));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::GetMenuWindowPtr(QWidget *menuWindow)
{
    this->menuWindow = menuWindow;
}

void GameWindow::on_btnMenu_clicked()
{
    if(timer != nullptr) {
        delete timer;
        timer = nullptr;
    }

    if(grid != nullptr) {
        delete grid;
        grid = nullptr;
    }

    if(opponentGrid != nullptr) {
        delete opponentGrid;
        opponentGrid = nullptr;
    }

    if(gameOverLabel != nullptr) {
        delete gameOverLabel;
        gameOverLabel = nullptr;
    }

    if(opponentGameOverLabel != nullptr) {
        delete opponentGameOverLabel;
        opponentGameOverLabel = nullptr;
    }

    menuWindow->show();
    this->close();
}

void GameWindow::on_btnReset_clicked()
{
    UpdateScoreLabel();
    delete currentBloc;
    PredictBloc();
  
    if(timer != nullptr) {
        delete timer;
        timer = nullptr;
    }

    if(grid != nullptr) {
        delete grid;
        grid = nullptr;
    }

    if(gameOverLabel != nullptr) {
        delete gameOverLabel;
        gameOverLabel = nullptr;
    }

    if(opponentGameOverLabel != nullptr) {
        delete opponentGameOverLabel;
        opponentGameOverLabel = nullptr;
    }

    InitializeGame();
}

void GameWindow::PredictBloc()
{
    int blocType = rand() % 7;
    switch(blocType) {
    case 0:
        nextBloc = new BlocL();
        break;
    case 1:
        nextBloc = new BlocI();
        break;
    case 2:
        nextBloc = new BlocO();
        break;
    case 3:
        nextBloc = new BlocT();
        break;
    case 4:
        nextBloc = new BlocJ();
        break;
    case 5:
        nextBloc = new BlocS();
        break;
    case 6:
        nextBloc = new BlocZ();
        break;
    }
    blocPred->SetNextBloc(nextBloc->GetForme(),nextBloc->GetColor());
}

void GameWindow::GenerateBloc()
{
    currentBloc = nextBloc;
    PredictBloc();
    PlaceBloc();
    setFocus();
}

void GameWindow::PlaceBloc()
{
    if(!grid->ColorGrid(currentBloc->GetForme(), blocPosition, blocPosition, currentBloc->GetColor(),DOWN)) {
        timer->stop();
    }

    sendMessage(' ');
}

void GameWindow::UpdateBlocPosition(int *difference, Direction direction) {
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

    sendMessage(' ');
}

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
            Score += 100 * (Niveau + 1);
            UpdateScoreLabel();
            break;
        case 3:
            Score += 300 * (Niveau + 1);
            UpdateScoreLabel();
            break;
        case 4:
            Score += 1200 * (Niveau + 1);
            UpdateScoreLabel();
            break;
    }
    blocPosition[0] = 3;
    blocPosition[1] = 0;
    GenerateBloc();
}

void GameWindow::gameOver(){
    timer->stop();
    gameOverLabel->show();
    gameOverLabel->activateWindow();
    gameOverLabel->raise();
    sendMessage('l');
}

void GameWindow::TimerEvent()
{
    int difference[2] = {0, 1};
    UpdateBlocPosition(difference, DOWN);
    }

void GameWindow::keyPressEvent(QKeyEvent *k) {
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
                    UpdateBlocPosition(diff_left, LEFT);
                    break;
                case 9:
                    UpdateBlocPosition(double_diff_left, LEFT);
                    break;
                }
            }
            currentBloc->RotateClockwise(blocPosition, grid);
            break;
        case Qt::Key_X:
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
                    UpdateBlocPosition(diff_left, LEFT);
                    break;
                case 9:
                    UpdateBlocPosition(double_diff_left, LEFT);
                    break;
                }
            }
            currentBloc->RotateCounterClockwise(blocPosition, grid);
            break;
    }
}

void GameWindow::ExcludeLine(int LineNumber) {
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
    }

    sendMessage(' ');
}

void GameWindow::attemptConnection()
{
    ui->btnReset->hide();
    // We use 127.0.0.1 (localhost)
    QString hostAddress = "127.0.0.1";
    // Tell the client to connect to the host using the port 7777
    m_playerClient->connectToServer(QHostAddress(hostAddress), 7777);
}

void GameWindow::connectedToServer()
{
    // once we connected to the server we ask the user for what username they would like to use
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"));
    if (newUsername.isEmpty()){
        // if the user clicked cancel or typed nothing, we just disconnect from the server
        return m_playerClient->disconnectFromHost();
    }
    // try to login with the given username
    attemptLogin(newUsername);
}

void GameWindow::attemptLogin(const QString &userName)
{
    // use the client to attempt a log in with the given username
    m_playerClient->login(userName);
}

void GameWindow::loggedIn()
{
    // once we successfully log in we enable the ui to display and send messages
    printf("LOGGEDIN");
}

void GameWindow::loginFailed(const QString &reason)
{
    // the server rejected the login attempt
    // display the reason for the rejection in a message box
    QMessageBox::critical(this, tr("Error"), reason);
    // allow the user to retry, execute the same slot as when just connected
    connectedToServer();
}

void GameWindow::messageReceived(const QString &sender, const QString &text)
{
    if(text.compare(QLatin1String("start"), Qt::CaseInsensitive) == 0)
        InitializeGame();
    else if(text.compare(QLatin1String("over"), Qt::CaseInsensitive) == 0) {
        opponentGameOverLabel->show();
        opponentGameOverLabel->activateWindow();
        opponentGameOverLabel->raise();
    }
    else
        opponentGrid->CopyState(text);
}

void GameWindow::sendMessage(QChar event)
{
    QString message;

    if(event == 's') // Start game
        message = "start";
    else if(event == 'l') // Game over
        message = "over";
    else // No event
        message = grid->SaveState();

    // we use the client to send the message
    m_playerClient->sendMessage(message);
}

void GameWindow::disconnectedFromServer()
{
    // if the client loses connection to the server
    // communicate the event to the user via a message box
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    // disable the ui to send and display messages
    on_btnMenu_clicked();
}

void GameWindow::userJoined(const QString &username)
{
    //QMessageBox::information(this, tr("User Joined"), tr("%1 Joined").arg(username));
    sendMessage('s');
    InitializeGame();
}

void GameWindow::userLeft(const QString &username)
{
    QMessageBox::information(this, tr("User Left"), tr("%1 Left").arg(username));
}

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

    //on_btnMenu_clicked();
}
