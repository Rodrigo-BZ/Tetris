/**
 * @file NextBlocPred.cpp
 * @brief This file implements the functions for the NextBlocPred class
 * @version 0.1
 * 
 */
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

/**
 * @brief This function constructs a grid of QLabel's that will display the next bloc.
 * 
 * @param gridParent The QWidget where the grid will be contained.
 * @param initialX The starting X position for the grid.
 * @param initialY The starting Y position for the grid.
 * @param cellWidth The width of each cell in the grid.
 * @param cellHeight The height of each cell in the grid.
 */
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

/**
 * @brief This function paints in the grid the next bloc.
 * 
 * @param bloc Int array that represents the shape of the next bloc.
 * @param color QColor object that contains the color of the next bloc.
 */
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

/**
 * @brief Clears the grid.
 * 
 */
void NextBlocPred::ClearGrid() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            labelGrid[i][j]->setStyleSheet("border-color: black;");
        }
    }
}
