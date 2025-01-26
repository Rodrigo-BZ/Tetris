#include "MenuWindow.h"
#include "./ui_MenuWindow.h"
#include <QDebug>


MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::GetGameWindowPtr(GameWindow *gameWindow)
{
    this->gameWindow = gameWindow;
}

void MenuWindow::on_btnPlay_clicked()
{
    if (gameWindow) {
        gameWindow->SetMultiPlayer(false);
        gameWindow->show();
        this->close();
    } else {
        qDebug() << "GameWindow not initialized!";
    }
}

void MenuWindow::on_btnMultiplayer_clicked()
{
    if (gameWindow) {
        gameWindow->SetMultiPlayer(true);
        gameWindow->show();
        this->close();
    } else {
        qDebug() << "GameWindow not initialized!";
    }
}

void MenuWindow::on_btnQuit_clicked()
{
    this->close();
}
