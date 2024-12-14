#ifndef CLASS_BLOC
#define CLASS_BLOC

#include <iostream>
#include <array>
#include QColor

class Bloc {
protected:
    std::array<std::array<int, 4>, 4> forme;
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

void Bloc::rotation90_clockwise() {
    std::array<std::array<int, 4>, 4> temp = forme;
    int n = forme.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < forme[i].size(); j++) {
            forme[j][n - 1 - i] = temp[i][j];
        }
    }
}

void Bloc::rotation90_counterclockwise() {
    std::array<std::array<int, 4>, 4> temp = forme;
    int n = forme.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < forme[i].size(); j++) {
            forme[n - 1 - j][i] = temp[i][j];
        }
    }
}

QColor getColor const() {return color;}


const std::array<std::array<int, 4>, 4>& Bloc::getForme() const {
    return forme;
}

#endif // CLASS_BLOC
