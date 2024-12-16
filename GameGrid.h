#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QPalette>
#include <QColor>
#include <array>

class GameGrid
{
public:
    GameGrid(QWidget *gridParent);
    GameGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
    ~GameGrid();

    int ColorGrid(std::array<std::array<int, 4>, 4> forme, int *position, int *initialPosition, QColor color);
    void UncolorGrid(std::array<std::array<int, 4>, 4> forme, int *position);

private:
    void ConstructGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
    QLabel *labelGrid[10][21];
};
#endif // GAMEGRID_H
