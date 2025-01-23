#ifndef CLASS_BLOC
#define CLASS_BLOC

#include <QColor>
#include <array>
#include "GameGrid.h"

class Bloc {
protected:
    std::array<std::array<int, 4>, 4> forme = {0};
    QColor color;
    GameGrid *gamegrid;
    int lenght;

public:
    Bloc(QColor c) : color(c) {};
    virtual ~Bloc() = default;

    bool IsValidRotation(int *position, GameGrid *grid);
    void RotateClockwise(int *position, GameGrid *grid);
    void RotateCounterClockwise(int *position, GameGrid *grid);
    bool FreeColumn(int columnNumber);
    std::array<std::array<int, 4>, 4> GetForme() const;
    QColor GetColor() const;
};

#endif // CLASS_BLOC
