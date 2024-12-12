#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void GetMenuWindowPtr(QWidget *menuWindow);

private slots:
    void on_btnMenu_clicked();
    void on_btnReset_clicked();

private:
    Ui::GameWindow *ui;
    QWidget *menuWindow;
};
#endif // GAMEWINDOW_H
