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

/**
 * @brief This function sets the value for the GameWindow object.
 * 
 * @param gameWindow GameWindow pointer object.
 */
void MenuWindow::GetGameWindowPtr(GameWindow *gameWindow)
{
    this->gameWindow = gameWindow;
}

/**
 * @brief This function is called when the play button in pressed. It opens a singleplayer game window.
 * 
 */
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

/**
 * @brief This function is called when the multiplayer button in pressed. It opens a multiplayer game window.
 * 
 */
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

/**
 * @brief This function is called when the tutorial button in pressed. It opens the tutorial for the game in a default browser.
 * 
 */
void MenuWindow::on_btnTutorial_clicked()
{
    QDesktopServices::openUrl(QUrl("https://docs.google.com/document/d/1HVUlN8MyU3eUpjFw6cgbhAKXsJG8_OLuDwjgXCkcigI/edit?usp=sharing", QUrl::TolerantMode));
}

/**
 * @brief This function is called when the quit button in pressed. It closes the application.
 * 
 */
void MenuWindow::on_btnQuit_clicked()
{
    this->close();
}
