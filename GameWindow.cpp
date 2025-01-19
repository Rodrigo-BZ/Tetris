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

    grid = new GameGrid(this, 250, 30, 30, 30);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->setInterval(100);

    setFocus();
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
            qDebug() << "Fixing block due to gravity.";
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
    blocPosition[0] = 3;
    blocPosition[1] = 0;
    timer->start();
    GenerateBloc();
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
    qDebug() << "Key pressed:" << k->key();
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
        case Qt::Key_Up:
            currentBloc->RotateClockwise(blocPosition, grid);
            break;
}
    HorizontalMove = false;
}