// #ifndef MENUWINDOW_H
// #define MENUWINDOW_H

#pragma once
#include <QMainWindow>
#include "GameWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

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

private:
    Ui::MenuWindow *ui;
    GameWindow *gameWindow;
};
// #endif // MENUWINDOW_H
