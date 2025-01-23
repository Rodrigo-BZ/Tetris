#ifndef NEXTBLOCPRED_H
#define NEXTBLOCPRED_H

#include <QWidget>
#include <QLabel>
#include <QColor>
#include <array>
#include <QDebug>

class NextBlocPred
{
public:
    NextBlocPred(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);
    ~NextBlocPred();

    void SetNextBloc(std::array<std::array<int, 4>, 4> bloc, QColor color);
    void ClearGrid();

private:
    void ConstructGrid(QWidget *gridParent, int initialX, int initialY, int cellWidth, int cellHeight);

    QLabel *labelGrid[4][4];
};

#endif // NEXTBLOCPRED_H
