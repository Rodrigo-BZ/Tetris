/**
 * @file GameGrid.cpp
 * @brief This file implements the functions for the GameGrid class
 * @version 0.1
 * 
 */
#include "GameGrid.h"

GameGrid::GameGrid(QWidget *gridParent)
{
    ConstructGrid(gridParent, 250, 30, 30, 30);
}

GameGrid::GameGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight)
{
    ConstructGrid(gridParent, initialX, initialY, cellWidth, cellHeight);
}

GameGrid::~GameGrid()
{
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 21; j++) {
            delete labelGrid[i][j];
        }
    }
}

/**
 * @brief This function returns the QLabel matrix that represents the game grid.
 * 
 * @return QLabel*(*)[21] 
 */
QLabel* (*GameGrid::GetLabelGrid())[21] {
    return labelGrid;
}

/**
 * @brief This function constructs a new empty grid but keeps it invisible. It is 10 cells wide and 21 cells high.
 * 
 * @param gridParent The QWidget that will contain the grid.
 * @param initialX The starting X position for the grid.
 * @param initialY The starting Y position for the grid.
 * @param cellWidth The width of each cell of the grid.
 * @param cellHeight The height of each cell of the grid
 */
void GameGrid::ConstructGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight)
{
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 21; j++) {
            labelGrid[i][j] = new QLabel(gridParent);
            labelGrid[i][j]->setGeometry(initialX + (i * cellWidth), initialY + (j * cellHeight), cellWidth, cellHeight);
            labelGrid[i][j]->setFrameShape(QFrame::Panel);
            labelGrid[i][j]->setLineWidth(3);

            QPalette palette = labelGrid[i][j]->palette();
            palette.setColor(QPalette::Window, Qt::gray);
            labelGrid[i][j]->setAutoFillBackground(true);
            labelGrid[i][j]->setPalette(palette);
            labelGrid[i][j]->setVisible(false);
        }
    }
}

/**
 * @brief This function sets the grid to visible.
 * 
 */
void GameGrid::Show()
{
    if(*labelGrid != nullptr) {
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 21; j++)
                labelGrid[i][j]->setVisible(true);
        }
    }
}

/**
 * @brief This function colors a certain Bloc piece in the grid.
 * 
 * @param forme The int array that represents the Bloc shape that will be painted.
 * @param position The position [x,y] where the bloc will be inserted.
 * @param initialPosition The bloc's initial position [x,y]. Can be equal to 'position' if the bloc has no previous position.
 * @param color The color of the bloc.
 * @param direction The direction in which the block is moving.
 * @return int 
 */
int GameGrid::ColorGrid(std::array<std::array<int, 4>, 4> forme, int *position, int *initialPosition, QColor color, Direction direction)
{
    int valid = 1;
    int toColor[4][2] = {-1};
    int k = 0;
    int blocLowerDelimiters[4] = {-1};
    int blocRightDelimiters[4] = {-1};
    int blocLeftDelimiters[4] = {-1};

    for(int a = 0; a < 4; a++) {
        for(int b = 0; b < 4; b++) {
            if(forme[b][a]) {
                if(b < 3) {
                    if(!forme[b + 1][a])
                        blocLowerDelimiters[a] = b;
                }
                else {
                    blocLowerDelimiters[a] = b;
                }
                if(a < 3) {
                    if(!forme[b][a + 1])
                        blocRightDelimiters[b] = a;
                }
                else {
                    blocRightDelimiters[b] = a;
                }
                if(a > 0) {
                    if(!forme[b][a - 1])
                        blocLeftDelimiters[b] = a;
                }
                else {
                    blocLeftDelimiters[b] = a;
                }
            }
        }
    }

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(forme[j][i]) {
                if(i + position[0] > 9 || i + position[0] < 0 || j + position[1] > 20) {
                    valid = 0;
                    break;
                }
                else if(labelGrid[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray &&
                        position == initialPosition) {
                    valid = 0;
                    break;
                }
                else if(direction == DOWN && labelGrid[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray &&
                        ((i == 0 && j == blocLowerDelimiters[0]) ||
                         (i == 1 && j == blocLowerDelimiters[1]) ||
                         (i == 2 && j == blocLowerDelimiters[2]) ||
                         (i == 3 && j == blocLowerDelimiters[3]))) {
                    valid = 0;
                    break;
                }
                else if(direction == RIGHT && labelGrid[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray &&
                         ((j == 0 && i == blocRightDelimiters[0]) ||
                          (j == 1 && i == blocRightDelimiters[1]) ||
                          (j == 2 && i == blocRightDelimiters[2]) ||
                          (j == 3 && i == blocRightDelimiters[3]))) {
                    valid = 0;
                    break;
                }
                else if(direction == LEFT && labelGrid[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray &&
                         ((j == 0 && i == blocLeftDelimiters[0]) ||
                          (j == 1 && i == blocLeftDelimiters[1]) ||
                          (j == 2 && i == blocLeftDelimiters[2]) ||
                          (j == 3 && i == blocLeftDelimiters[3]))) {
                    valid = 0;
                    break;
                }
                else {
                    toColor[k][0] = i + position[0];
                    toColor[k][1] = j + position[1];
                    k++;
                }
            }
        }
    }

    if(valid) {
        UncolorGrid(forme, initialPosition);

        for(int l = 0; l < 4; l++) {
            if(toColor[l][0] != -1 && toColor[l][1] != -1) {
                QPalette palette = labelGrid[toColor[l][0]][toColor[l][1]]->palette();
                palette.setColor(QPalette::Window, color);
                labelGrid[toColor[l][0]][toColor[l][1]]->setPalette(palette);
            }
        }
    }

    return valid;
}

/**
 * @brief This function uncolors a certain Bloc piece in the grid.
 * 
 * @param forme The int array that represents the Bloc shape that will be erased.
 * @param position The position of the bloc in the grid.
 */
void GameGrid::UncolorGrid(std::array<std::array<int, 4>, 4> forme, int *position)
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(forme[j][i])
                labelGrid[i + position[0]][j + position[1]]->setPalette(Qt::gray);
        }
    }
}

/**
 * @brief This function returns a QSting containing a replica of the current grid state.
 * 
 * @return QString 
 */
QString GameGrid::SaveState()
{
    QString state;
    state.resize(210, ' ');

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 21; j++) {
            QChar saved;
            QColor color = labelGrid[i][j]->palette().color(QPalette::Window);

            if(color == Qt::gray)
                saved = 'G';
            else if(color == QColor(255,165,0))
                saved = 'o';
            else if(color == QColor(0,255,255))
                saved = 'c';
            else if(color == QColor(255,255,0))
                saved = 'y';
            else if(color == QColor(128,0,128))
                saved = 'p';
            else if(color == QColor(0,0,255))
                saved = 'b';
            else if(color == QColor(0,255,0))
                saved = 'g';
            else if(color == QColor(255,0,0))
                saved = 'r';
            else if(color == Qt::black)
                saved = 'B';

            state[j + (i * 21)] = saved;
        }
    }

    return state;
}

/**
 * @brief This function copies another grid state.
 * 
 * @param oppState A QString containing the replica of the grid state.
 */
void GameGrid::CopyState(QString oppState)
{
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 21; j++) {
            QPalette palette = labelGrid[i][j]->palette();
            QChar received = oppState[j + (i * 21)];

            if(received == 'G')
                palette.setColor(QPalette::Window, Qt::gray);
            else if(received == 'o')
                palette.setColor(QPalette::Window, QColor(255,165,0));
            else if(received == 'c')
                palette.setColor(QPalette::Window, QColor(0,255,255));
            else if(received == 'y')
                palette.setColor(QPalette::Window, QColor(255,255,0));
            else if(received == 'p')
                palette.setColor(QPalette::Window, QColor(128,0,128));
            else if(received == 'b')
                palette.setColor(QPalette::Window, QColor(0,0,255));
            else if(received == 'g')
                palette.setColor(QPalette::Window, QColor(0,255,0));
            else if(received == 'r')
                palette.setColor(QPalette::Window, QColor(255,0,0));
            else if(received == 'B')
                palette.setColor(QPalette::Window, Qt::black);

            labelGrid[i][j]->setPalette(palette);
        }
    }
}

/**
 * @brief This function adds a 'Garbage Line' to the bottom of a grid.
 * 
 * @param forme The int array that represents the Bloc shape of the current falling bloc.
 * @param position The position of the current falling bloc.
 */
void GameGrid::AddLineBottom(std::array<std::array<int, 4>, 4> forme, int *position)
{
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            bool intoBloc = false;
            if((i >= position[0] && i <= position[0] + 3) && (j + 1 >= position[1] && j + 1 <= position[1] + 3)) { // 1 above current 4x4
                intoBloc = forme[j+1-position[1]][i-position[0]]; // moving bloc cant be copied
            }
            if(!intoBloc)
                (labelGrid[i][j]->setPalette(labelGrid[i][j + 1]->palette()));
        }
    }

    int hole = rand() % 10;
    for(int i = 0; i < 10; i++) {
        if(i != hole)
            labelGrid[i][20]->setPalette(Qt::black);
        else
            labelGrid[i][20]->setPalette(Qt::gray);
    }
}
