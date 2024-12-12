#include "GameWindow.h"
#include "./ui_GameWindow.h"

#include <QLabel>
#include <QFrame>
#include <QPalette>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    QLabel *label = new QLabel(this);
    label->setGeometry(100, 100, 50, 50);

    QPalette palette = label->palette();
    palette.setColor(QPalette::Window, Qt::gray);
    label->setAutoFillBackground(true);
    label->setPalette(palette);
    label->setVisible(true);

    label->setFrameShape(QFrame::Panel);
    label->setLineWidth(3);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::GetMenuWindowPtr(QWidget *menuWindow)
{
    this->menuWindow = menuWindow;
};

void GameWindow::on_btnMenu_clicked()
{
    menuWindow->show();
    this->close();
}

void GameWindow::on_btnReset_clicked()
{
    //implement
}
