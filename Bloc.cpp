#include "Bloc.h"

void Bloc::RotateClockwise(int *position, GameGrid *grid)
{
    std::array<std::array<int, 4>, 4> temp = forme;

    if(lenght == 9){
        if(position[0] < 0 || position[0] > 7){
            return;
        }
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(forme[j][i])
                    grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(Qt::gray);
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                forme[j][2 - i] = temp[i][j];
            }
        }

    } else {
        if(position[0]<0 || position[0]>6){
            return;
        }

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
}

void Bloc::RotateCounterClockwise(int *position, GameGrid *grid)
{
    std::array<std::array<int, 4>, 4> temp = forme;

    if(lenght == 9){
        if(position[0] < 0 || position[0] > 7){
            return;
        }
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(forme[j][i])
                    grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(Qt::gray);
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                forme[2 - j][i] = temp[i][j];
            }
        }

    } else {
        if(position[0]<0 || position[0]>6){
            return;
        }

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(forme[j][i])
                    grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(Qt::gray);
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                forme[3 - j][i] = temp[i][j];
            }
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
