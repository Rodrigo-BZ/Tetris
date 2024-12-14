#ifndef CLASS_BLOC
#define CLASS_BLOC

#include <iostream>
#include QColor

class Bloc {
protected:
    int forme[4][4];
    QColor color;      // Cor da peça

public:
    Bloc(QColor c) : color(c), orientation(0) {
        forme = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
    };
    void rotation90_clockwise();
    void rotation90_counterclockwise();
    const std::array<std::array<int, 4>, 4>& getForme() const;
    QColor getColor const();
    virtual ~Bloc() = default;
};

#endif // CLASS_BLOC
