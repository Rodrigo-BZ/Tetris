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
