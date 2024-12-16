// #ifndef MENUWINDOW_H
// #define MENUWINDOW_H

#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

    void GetGameWindowPtr(QWidget *gameWindow);

private slots:
    void on_btnPlay_clicked();

private:
    Ui::MenuWindow *ui;
    QWidget *gameWindow;
};
// #endif // MENUWINDOW_H
