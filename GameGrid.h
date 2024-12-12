#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QPalette>

class GameGrid
{
public:
    GameGrid(QWidget *gridParent);
    GameGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
    ~GameGrid();

private:
    void ConstructGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
    QLabel *labelGrid[10][21];
};
#endif // GAMEGRID_H
