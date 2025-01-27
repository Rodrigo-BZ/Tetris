/**
 * @file GameWindow.h
 * @brief Header file for the GameWindow class
 * @version 0.1
 * 
 */
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

/**
 * @brief This class represents the GameWindow. It functions as a game manager, handling all player interactions during the game.
 * 
 */
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
    void AddLinePenalty();
    void gameOver();
    void Victory();
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
    /// @brief Boolean attribute to indicate if the game is singleplayer or multiplayer.
    bool multip = false;
    /// @brief Boolean attribute to prevent player movements when it is necessary.
    bool allowMovements = false;
    /// @brief Int vector representing the position of the current falling Bloc piece.
    int blocPosition[2] = {3, 0};
    int currentKey;
    /// @brief Int value that indicates the current Level during the game.
    int Niveau;
    /// @brief Int value that stores the number of lines cleared during the game. It grows from 0 to 9, and when it reaches 10, the value of Level goes up by 1 and this returns to 0.
    int linesCleared;
    /// @brief Int value that stores the number of lines cleared in a single move. Used to calculate points obtained and number of garbage lines sent to opponent.
    int linesClearedatOnce;
    /// @brief Int value that indicates the current player's score.
    int Score = 0;
    /// @brief Ui object from the Qt libraries that contains the game window's visual elements.
    Ui::GameWindow *ui;
    /// @brief QWidget pointer to the menu window, for toggling between windows.
    QWidget *menuWindow;
    /// @brief QString that stores the current player's username.
    QString playerName;
    /// @brief Smart unique pointer to an object of the class NextBlocPred. Contains the next Bloc piece prediction.
    std::unique_ptr<NextBlocPred> blocPred;
    /// @brief Smart unique pointer to an object of the class QTimer. Contains the timer used for making pieces fall.
    std::unique_ptr<QTimer> timer;
    /// @brief Smart unique pointer to an object of the class GameGrid. Contains the current player's grid.
    std::unique_ptr<GameGrid> grid;
    /// @brief Smart unique pointer to an object of the class GameGrid. Contains the opponent player's grid.
    std::unique_ptr<GameGrid> opponentGrid;
    /// @brief Smart shared pointer to an object of the class Bloc. Contains the current falling Bloc piece.
    std::shared_ptr<Bloc> currentBloc;
    /// @brief Smart shared pointer to an object of the class Bloc. Contains the next Bloc piece that will be inserted once the current one is fixed.
    std::shared_ptr<Bloc> nextBloc;
    /// @brief Smart unique pointer to an object of the class QLabel. Contains the label used to display the current player's score.
    std::unique_ptr<QLabel> scoreLabel;
    /// @brief Smart unique pointer to an object of the class QLabel. Contains the label used to display the current level during the game.
    std::unique_ptr<QLabel> levelLabel;
    /// @brief Smart unique pointer to an object of the class QLabel. Contains the label used to display the "Next Bloc" text.
    std::unique_ptr<QLabel> predLabel;
    /// @brief Smart unique pointer to an object of the class QLabel. Contains the label used to display the "VICTORY" or "GAME OVER" texts for the current player.
    std::unique_ptr<QLabel> gameOverLabel;
    /// @brief Smart unique pointer to an object of the class QLabel. Contains the label used to display the "VICTORY" or "GAME OVER" texts for the opponent player.
    std::unique_ptr<QLabel> opponentGameOverLabel;
    /// @brief Smart unique pointer to an object of the class QLabel. Contains the label used to display the "Waiting for opponent to connect..." text.
    std::unique_ptr<QLabel> waitingOpponentLabel;
    /// @brief Smart unique pointer to an object of the class QLabel. Contains the label used to display the current player's username.
    std::unique_ptr<QLabel> playerNameLabel;
    /// @brief Smart unique pointer to an object of the class QLabel. Contains the label used to display the opponent player's username.
    std::unique_ptr<QLabel> opponentNameLabel;
    /// @brief Smart unique pointer to an object of the class PlayerClient. Contains the object that handles TCP communications between the player and the server.
    std::unique_ptr<PlayerClient> m_playerClient;
};
#endif // GAMEWINDOW_H
