#include "GameWindow.h"
#include "./ui_GameWindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
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
