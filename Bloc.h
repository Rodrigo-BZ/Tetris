/**
 * @file Bloc.h
 * @brief Header file for the Bloc class
 * @version 0.1
 * 
 */
#ifndef CLASS_BLOC
#define CLASS_BLOC

#include <QColor>
#include <array>
#include "GameGrid.h"

/**
 * @brief This class represents the Bloc piece. It handles all actions that are performed by all Bloc types.
 * 
 */
class Bloc {
protected:
    /// The int array that represents the Bloc piece shape.
    std::array<std::array<int, 4>, 4> forme = {0}; 
    /// The QColor attribute to indicate the color of the Bloc piece.
    QColor color;
    /// This corresponds to the matrix size necessary for representing the piece.
    int lenght;

public:
    Bloc(QColor c) : color(c) {};
    virtual ~Bloc() = default;

    void RotateClockwise(int *position, GameGrid *grid);
    void RotateCounterClockwise(int *position, GameGrid *grid);
    bool FreeColumn(int columnNumber);
    std::array<std::array<int, 4>, 4> GetForme() const;
    QColor GetColor() const;
    int GetLenght() const;
};

#endif // CLASS_BLOC
