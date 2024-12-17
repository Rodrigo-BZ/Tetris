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

}

QLabel* (*GameGrid::GetLabelGrid())[21] {
    return labelGrid;
}

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
            labelGrid[i][j]->setVisible(true);
        }
    }
}

int GameGrid::ColorGrid(std::array<std::array<int, 4>, 4> forme, int *position, int *initialPosition, QColor color)
{
    int valid = 1;
    int toColor[4][2] = {-1};
    int k = 0;
    int blocLowerDelimiters[4] = {-1};

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
                else if(labelGrid[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray &&
                        ((i == 0 && j == blocLowerDelimiters[0]+1) ||
                         (i == 1 && j == blocLowerDelimiters[1]+1) ||
                         (i == 2 && j == blocLowerDelimiters[2]+1) ||
                         (i == 3 && j == blocLowerDelimiters[3]+1))) {
                    qDebug() << "Collision";
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

void GameGrid::UncolorGrid(std::array<std::array<int, 4>, 4> forme, int *position)
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(forme[j][i])
                labelGrid[i + position[0]][j + position[1]]->setPalette(Qt::gray);
        }
    }
}
