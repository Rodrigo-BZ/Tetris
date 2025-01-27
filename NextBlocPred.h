/**
 * @file NextBlocPred.h
 * @brief Header file for the NextBlocPred class
 * @version 0.1
 * 
 */
#ifndef NEXTBLOCPRED_H
#define NEXTBLOCPRED_H

#include <QWidget>
#include <QLabel>
#include <QColor>
#include <array>
#include <QDebug>

/**
 * @brief This class representes the prediction for the next bloc int the game. It contains a mini grid for representing it and handles modifications to it.
 * 
 */
class NextBlocPred
{
public:
    NextBlocPred(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
    ~NextBlocPred();

    void SetNextBloc(std::array<std::array<int, 4>, 4> bloc, QColor color);
    void ClearGrid();

private:
    void ConstructGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);

    /// @brief Matrix of QLabel objects used to represent the next bloc.
    QLabel *labelGrid[4][4];
};

#endif // NEXTBLOCPRED_H
