#include "GameWindow.h"
#include "./ui_GameWindow.h"

void GameWindow::focusInEvent(QFocusEvent *event) {
    setFocus();
    QMainWindow::focusInEvent(event);
}

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    InitializeScoreWidget();

    grid = new GameGrid(this, 250, 30, 30, 30);
    timer = new QTimer(this);
    Niveau = 0;
    linesCleared = 0;
    Score = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->setInterval(600);

    setFocus();
}

void GameWindow::InitializeScoreWidget() {
    scoreLabel = new QLabel("Score: 0", this);

    scoreLabel->setGeometry(width() - 220, 160, 200, 30);
    scoreLabel->setStyleSheet("font-size: 16px; color: black;");

    scoreLabel->show();

    levelLabel = new QLabel("Level: 0", this);

    levelLabel->setGeometry(width()-220, 200, 200, 30);
    levelLabel->setStyleSheet("font-size: 16px; color: black;");

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
    menuWindow->show();
    this->close();
}

void GameWindow::on_btnReset_clicked()
{
    grid = new GameGrid(this, 250, 30, 30, 30);
    timer = new QTimer(this);
    Niveau = 0;
    linesCleared = 0;
    Score = 0;
    delete currentBloc;
    blocPosition[0] = 3;
    blocPosition[1] = 0;
    GenerateBloc();
    timer->setInterval(600);
}

void GameWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);
    GenerateBloc();
    timer->start();
}

void GameWindow::GenerateBloc()
{
    int blocType = rand() % 7;
    switch(blocType) {
        case 0:
            currentBloc = new BlocL();
            break;
        case 1:
            currentBloc = new BlocI();
            break;
        case 2:
            currentBloc = new BlocO();
            break;
        case 3:
            currentBloc = new BlocT();
            break;
        case 4:
            currentBloc = new BlocJ();
            break;
        case 5:
            currentBloc = new BlocS();
            break;
        case 6:
            currentBloc = new BlocZ();
            break;
    }
    PlaceBloc();
    setFocus();
}

void GameWindow::PlaceBloc()
{
    if(!grid->ColorGrid(currentBloc->GetForme(), blocPosition, blocPosition, currentBloc->GetColor(),DOWN)) {
        timer->stop(); //Implement game over
    }
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
}


void GameWindow::FixBloc()
{
    timer->stop();
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
    timer->start();
    GenerateBloc();
}

void GameWindow::gameOver(){
    timer->stop();

    QLabel *gameOverLabel = new QLabel("GAME OVER", this);
    gameOverLabel->setGeometry(150, 200, 300, 100);
    gameOverLabel->setStyleSheet("font-size: 32px; color: red; font-weight: bold;");
    gameOverLabel->setAlignment(Qt::AlignCenter);
    int x = (width() - 300) / 2; 
    int y = (height() - 100) / 2;
    gameOverLabel->setGeometry(x, y, 300, 100);
    gameOverLabel->show();

    QPushButton *menuButton = new QPushButton("Voltar ao Menu", this);
    menuButton->setGeometry(x + 75, y + 90, 150, 40);
    connect(menuButton, &QPushButton::clicked, this, &GameWindow::on_btnMenu_clicked);
    menuButton->show();

}

void GameWindow::TimerEvent()
{
    if (!lastManualMove) {
        int difference[2] = {0, 1};
        UpdateBlocPosition(difference, DOWN);
    }
    lastManualMove = false; 
}

void GameWindow::keyPressEvent(QKeyEvent *k) {
    lastManualMove = true;
    int diff_left[2] = {-1,0};
    int diff_right[2] = {1,0};
    int diff_down[2] = {0,1};
    switch (k -> key()) {
        case Qt::Key_Left:
            HorizontalMove = true;
            UpdateBlocPosition(diff_left, LEFT);
            break;
        case Qt::Key_Right:
            HorizontalMove = true;
            UpdateBlocPosition(diff_right, RIGHT);
            break;
        case Qt::Key_Down:
            UpdateBlocPosition(diff_down, DOWN);
            break;
        case Qt::Key_Z:
            currentBloc->RotateClockwise(blocPosition, grid);
            break;
        case Qt::Key_X:
            currentBloc->RotateCounterClockwise(blocPosition, grid);
            break;
}
    HorizontalMove = false;
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
}
