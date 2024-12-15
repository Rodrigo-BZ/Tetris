#ifndef CLASS_BLOC
#define CLASS_BLOC

#include <QColor>
#include <array>

class Bloc {
protected:
    std::array<std::array<int, 4>, 4> forme = {0};
    QColor color;

public:
    Bloc(QColor c) : color(c) {};
    virtual ~Bloc() = default;

    void RotateClockwise();
    void RotateCounterClockwise();
    std::array<std::array<int, 4>, 4> GetForme() const;
    QColor GetColor() const;
};

#endif // CLASS_BLOC
