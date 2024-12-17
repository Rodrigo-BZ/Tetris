#include "GameWindow.h"
#include "./ui_GameWindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    grid = new GameGrid(this, 250, 30, 30, 30);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->setInterval(100);
    this->setFocusPolicy(Qt::StrongFocus);

    keyTimer = new QTimer(this);  // Instantiate keyTimer
    connect(keyTimer, &QTimer::timeout, this, &GameWindow::handleKeyMovement);
    keyTimer->setInterval(50);
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
    //implement
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
}

void GameWindow::PlaceBloc()
{
    if(!grid->ColorGrid(currentBloc->GetForme(), blocPosition, blocPosition, currentBloc->GetColor())) {
        timer->stop(); //Implement game over
    }
}

void GameWindow::UpdateBlocPosition(int *difference)
{
    int initialPosition[2] = {blocPosition[0], blocPosition[1]};
    blocPosition[0] += difference[0];
    blocPosition[1] += difference[1];
    if(!grid->ColorGrid(currentBloc->GetForme(), blocPosition, initialPosition, currentBloc->GetColor())) {
        FixBloc();
    }
}

void GameWindow::FixBloc()
{
    timer->stop();
    blocPosition[0] = 3;
    blocPosition[1] = 0;
    timer->start();
    GenerateBloc();
}

void GameWindow::TimerEvent()
{
    int difference[2] = {0, 1};
    UpdateBlocPosition(difference);
}

void GameWindow::keyPressEvent(QKeyEvent *k) {
    currentKey = k->key(); // Store the pressed key
    if (!keyTimer->isActive()) {
        keyTimer->start(100); // Adjust the interval as needed
    }
}


void GameWindow::handleKeyMovement() {
    if (currentKey == -1) return;

    switch (currentKey) {
        case Qt::Key_Left:
            if(blocPosition[0]>0){
                blocPosition[0] -= 1;
                PlaceBloc();
            }
            break;
        case Qt::Key_Right:
            if (blocPosition[0] < 10) {
                blocPosition[0] += 1;
                PlaceBloc();
            }
            break;
        case Qt::Key_Down:
            blocPosition[1] += 1;
            PlaceBloc();
            break;
        case Qt::Key_Up:
            currentBloc->RotateClockwise();
            PlaceBloc();
            break;
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *k) {
    if (k->key() == currentKey) {
        keyTimer->stop();
        currentKey = -1; // Reset the key
    }
}
