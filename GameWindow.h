#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFrame>
#include <QPalette>
#include <QTimer>
#include <cstdlib>
#include <QKeyEvent>
#include "GameGrid.h"
#include "BlocTypes.h"
#include <QDebug>

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
    void SetMultiPlayer(bool multip);

private slots:
    void on_btnMenu_clicked();
    void on_btnReset_clicked();
    void GenerateBloc();
    void PlaceBloc();
    void UpdateBlocPosition(int *difference, Direction direction);
    void FixBloc();
    void TimerEvent();
    void keyPressEvent(QKeyEvent *k);
    void focusInEvent(QFocusEvent *event);
    void ExcludeLine(int LineNumber);
    void gameOver();
    void InitializeGame();

private:
    bool multip = false;
    Ui::GameWindow *ui;
    QWidget *menuWindow;
    QTimer *timer;
    GameGrid *grid;
    GameGrid *opponentGrid;
    Bloc *currentBloc;
    int blocPosition[2] = {3, 0};
    QTimer* keyTimer;
    int currentKey;
    bool lastManualMove = false;
    bool HorizontalMove;
    int Niveau;
    int linesCleared;
    int linesClearedatOnce;
    int Score = 0;
    QLabel *scoreLabel; 
    QLabel *levelLabel;
    QLabel *gameOverLabel = nullptr;
    void InitializeScoreWidget(); 
    void UpdateScoreLabel();
};
#endif // GAMEWINDOW_H
