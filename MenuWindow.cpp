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

void MenuWindow::GetGameWindowPtr(QWidget *gameWindow)
{
    this->gameWindow = gameWindow;
}

void MenuWindow::on_btnPlay_clicked()
{
    if (gameWindow) {
        gameWindow->show();
        this->close();
    } else {
        qDebug() << "GameWindow not initialized!";
    }
}

