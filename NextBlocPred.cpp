#include "NextBlocPred.h"

NextBlocPred::NextBlocPred(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight) {
    ConstructGrid(gridParent, initialX, initialY, cellWidth, cellHeight);
}

NextBlocPred::~NextBlocPred() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            delete labelGrid[i][j];
        }
    }
}

void NextBlocPred::ConstructGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            labelGrid[i][j] = new QLabel(gridParent);
            labelGrid[i][j]->setFixedSize(cellWidth, cellHeight);

            labelGrid[i][j]->setStyleSheet("border-width: 2px; border-color: black;");
            labelGrid[i][j]->move(initialX + j * cellWidth, initialY + i * cellHeight);
            labelGrid[i][j]->show();
        }
    }
}

void NextBlocPred::SetNextBloc(std::array<std::array<int, 4>, 4> bloc, QColor color) {
    ClearGrid();

    QString styleSheet = QString("background-color: %1; border: 1px solid black;").arg(color.name());

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (bloc[i][j] == 1) {
                labelGrid[i][j]->setStyleSheet(styleSheet);
            }
        }
    }
}

void NextBlocPred::ClearGrid() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            labelGrid[i][j]->setStyleSheet("border-color: black;");
        }
    }
}
