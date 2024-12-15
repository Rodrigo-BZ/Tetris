#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFrame>
#include <QPalette>
#include <QTimer>
#include <cstdlib>
#include "GameGrid.h"
#include "BlocTypes.h"

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
    void showEvent(QShowEvent* event);
    void GenerateBloc();
    void PlaceBloc();
    void UpdateBlocPosition(int *difference);
    void FixBloc();
    void TimerEvent();

private:
    Ui::GameWindow *ui;
    QWidget *menuWindow;
    QTimer *timer;
    GameGrid *grid;
    Bloc *currentBloc;
    int blocPosition[2] = {3, 0};
};
#endif // GAMEWINDOW_H
