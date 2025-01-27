/**
 * @file GameGrid.h
 * @brief Header file for the GameGrid class
 * @version 0.1
 * 
 */
#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QPalette>
#include <QColor>
#include <array>
#include <QDebug>
#include "GameEnums.h"

/**
 * @brief This class representes the game grid of labels. It handles all modifications of the grid during the game.
 * 
 */
class GameGrid : QWidget
{
public:
    GameGrid(QWidget *gridParent);
    GameGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
    ~GameGrid();

public slots:
    int ColorGrid(std::array<std::array<int, 4>, 4> forme, int *position, int *initialPosition, QColor color, Direction direction);
    void UncolorGrid(std::array<std::array<int, 4>, 4> forme, int *position);
    void CopyState(QString oppState);
    void Show();
    void AddLineBottom(std::array<std::array<int, 4>, 4> forme, int *position);
    QString SaveState();
    QLabel* (*GetLabelGrid())[21];

private:
    /// @brief This object contains a pointer to a matrix of QLabel objects. They are used to show the grid on the screen.
    QLabel *labelGrid[10][21];

private slots:
    void ConstructGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
};

#endif
