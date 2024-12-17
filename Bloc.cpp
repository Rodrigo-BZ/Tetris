#include "Bloc.h"

void Bloc::RotateClockwise(int *position, GameGrid *grid)
{
    std::array<std::array<int, 4>, 4> temp = forme;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(forme[j][i])
                grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(Qt::gray);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            forme[j][3 - i] = temp[i][j];
        }
    }
}

void Bloc::RotateCounterClockwise()
{
    std::array<std::array<int, 4>, 4> temp = forme;
    int n = forme.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < forme[i].size(); j++) {
            forme[n - 1 - j][i] = temp[i][j];
        }
    }
}

QColor Bloc::GetColor() const
{
    return color;
}

std::array<std::array<int, 4>, 4> Bloc::GetForme() const
{
    return forme;
}
