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

class GameGrid
{
public:
    GameGrid(QWidget *gridParent);
    GameGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
    ~GameGrid();

    int ColorGrid(std::array<std::array<int, 4>, 4> forme, int *position, int *initialPosition, QColor color, Direction direction);
    void UncolorGrid(std::array<std::array<int, 4>, 4> forme, int *position);
    QLabel* (*GetLabelGrid())[21];

private:
    void ConstructGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
    QLabel *labelGrid[10][21];

};
#endif
