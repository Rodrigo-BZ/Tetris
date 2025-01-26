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
#include "NextBlocPred.h"
#include "PlayerClient.h"
#include <QMessageBox>
#include <QInputDialog>

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
    void PredictBloc();
    void PlaceBloc();
    void UpdateBlocPosition(int *difference, Direction direction);
    void FixBloc();
    void TimerEvent();
    void keyPressEvent(QKeyEvent *k);
    void focusInEvent(QFocusEvent *event);
    void ExcludeLine(int LineNumber);
    void gameOver();
    void InitializeGame();

    void attemptConnection();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    void loggedIn();
    void loginFailed(const QString &reason);
    void messageReceived(const QString &sender, const QString &text);
    void sendMessage(QChar event);
    void disconnectedFromServer();
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void error(QAbstractSocket::SocketError socketError);

private:
    bool multip = false;
    Ui::GameWindow *ui;
    QWidget *menuWindow;
    NextBlocPred *blocPred;
    QTimer *timer = nullptr;
    GameGrid *grid = nullptr;
    GameGrid *opponentGrid = nullptr;
    Bloc *currentBloc;
    Bloc *nextBloc;
    int blocPosition[2] = {3, 0};
    QTimer* keyTimer;
    int currentKey;
    int Niveau;
    int linesCleared;
    int linesClearedatOnce;
    int Score = 0;
    QLabel *scoreLabel; 
    QLabel *levelLabel;
    QLabel *predLabel;
    QLabel *gameOverLabel = nullptr;
    QLabel *opponentGameOverLabel = nullptr;
    void InitializeScoreWidget(); 
    void UpdateScoreLabel();

    PlayerClient *m_playerClient;
};
#endif // GAMEWINDOW_H
