#ifndef CLASS_BLOC
#define CLASS_BLOC

#include <iostream>
#include <array>

class Bloc {
protected:
    std::array<std::array<int, 4>, 4> forme; // Array 2D
    int direction;  // Direção atual da peça
    int kind;       // Tipo da peça
    int orientation; // Orientação atual
    int color;      // Cor da peça

public:
    // Construtor
    Bloc(int kind, int color);

    // Métodos
    void rotation90();
    const std::array<std::array<int, 4>, 4>& getForme() const; 
    virtual ~Bloc() = default;
};

Bloc::Bloc(int k, int c) : kind(k), color(c), direction(0), orientation(0) {
    forme = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
}

void Bloc::rotation90() {
    std::array<std::array<int, 4>, 4> temp = forme;
    int n = forme.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < forme[i].size(); j++) {
            forme[j][n - 1 - i] = temp[i][j];
        }
    }
    direction = (direction + 1) % 4; 
}

const std::array<std::array<int, 4>, 4>& Bloc::getForme() const {
    return forme;
}

#endif // CLASS_BLOC
