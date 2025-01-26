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
            labelGrid[i][j]->setVisible(false);
        }
    }
}

void GameGrid::Show()
{
    if(*labelGrid != nullptr) {
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 21; j++)
                labelGrid[i][j]->setVisible(true);
        }
    }
}

int GameGrid::ColorGrid(std::array<std::array<int, 4>, 4> forme, int *position, int *initialPosition, QColor color, Direction direction)
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
                else if(direction == DOWN && labelGrid[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray &&
                        ((i == 0 && j == blocLowerDelimiters[0]) ||
                         (i == 1 && j == blocLowerDelimiters[1]) ||
                         (i == 2 && j == blocLowerDelimiters[2]) ||
                         (i == 3 && j == blocLowerDelimiters[3]))) {
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

            state[j + (i * 21)] = saved;
        }
    }

    return state;
}

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

            labelGrid[i][j]->setPalette(palette);
        }
    }
}
