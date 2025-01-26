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
    void on_btnConnect_clicked();
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
    void ResetUi(bool multip);
    void InitializePredictionWidget(int labelStartingX, int blocStartingX);
    void InitializeScoreWidget(int startingX);
    void UpdateScoreLabel();

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
    bool allowMovements = false;
    int blocPosition[2] = {3, 0};
    int currentKey;
    int Niveau;
    int linesCleared;
    int linesClearedatOnce;
    int Score = 0;

    Ui::GameWindow *ui;
    QWidget *menuWindow;
    QString playerName;

    std::unique_ptr<NextBlocPred> blocPred;
    std::unique_ptr<QTimer> timer;
    std::unique_ptr<GameGrid> grid;
    std::unique_ptr<GameGrid> opponentGrid;
    std::shared_ptr<Bloc> currentBloc;
    std::shared_ptr<Bloc> nextBloc;
    std::unique_ptr<QLabel> scoreLabel;
    std::unique_ptr<QLabel> levelLabel;
    std::unique_ptr<QLabel> predLabel;
    std::unique_ptr<QLabel> gameOverLabel;
    std::unique_ptr<QLabel> opponentGameOverLabel;
    std::unique_ptr<QLabel> waitingOpponentLabel;
    std::unique_ptr<QLabel> playerNameLabel;
    std::unique_ptr<QLabel> opponentNameLabel;

    std::unique_ptr<PlayerClient> m_playerClient;
};
#endif // GAMEWINDOW_H
