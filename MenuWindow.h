/**
 * @file MenuWindow.h
 * @brief Header file for the MenuWindow class
 * @version 0.1
 * 
 */
// #ifndef MENUWINDOW_H
// #define MENUWINDOW_H

#pragma once
#include <QMainWindow>
#include <QDesktopServices>
#include "GameWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

/**
 * @brief This class represents the MenuWindow. It functions as a menu manager, handling all user interactions in the menu screen.
 * 
 */
class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

    void GetGameWindowPtr(GameWindow *gameWindow);

private slots:
    void on_btnPlay_clicked();
    void on_btnMultiplayer_clicked();
    void on_btnTutorial_clicked();
    void on_btnQuit_clicked();

private:
    /// @brief Ui object from the Qt libraries that contains the menu window's visual elements.
    Ui::MenuWindow *ui;
    /// @brief QWidget pointer to the game window, for toggling between windows.
    GameWindow *gameWindow;
};
// #endif // MENUWINDOW_H
