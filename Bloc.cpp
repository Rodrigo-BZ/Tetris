#include "Bloc.h"

void Bloc::RotateClockwise(int *position, GameGrid *grid)
{
    std::array<std::array<int, 4>, 4> temp = forme;
    bool otherBlocksNear = false;
    bool otherBlocksNear_left = false;
    bool otherBlocksNear_right = false;
    bool otherBlocksNear_down = false;

    if(lenght == 9){
        if(position[1] > 17){
            return;
        }
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(forme[j][i]){
                    grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(Qt::gray);
                }
                else if(grid->GetLabelGrid()[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                    otherBlocksNear = true;
                }
            }
        }
        if(otherBlocksNear){
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++){
                    if(grid->GetLabelGrid()[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                        if(i == 2){
                            otherBlocksNear_down = true;
                        }
                        if(i == 1 || i == 0){
                            otherBlocksNear_left = true;
                        }
                        if(i == 3 || i == 2){
                            otherBlocksNear_right = true;
                        }
                    }
                }
            }
        }
        if((otherBlocksNear_left && otherBlocksNear_right) || otherBlocksNear_down){
            forme = temp;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(forme[j][i]){
                        grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
                    }
                }
            }
            return;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(otherBlocksNear && grid->GetLabelGrid()[j + position[0]][2 - i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                    if(j <= 1){
                        position[0] += 1;
                    }
                    else{
                        if(grid->GetLabelGrid()[j - 1 + position[0]][2 - i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                            position[0] -= 1;
                        }
                        else{
                            forme = temp;
                            for(int i = 0; i < 3; i++) {
                                for(int j = 0; j < 3; j++) {
                                    if(forme[j][i]){
                                        grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
                                    }
                                }
                            }
                            return;
                        }
                    }
                }
                forme[j][2 - i] = temp[i][j];
            }
        }

    } else {
        if(position[1] > 17){
            return;
        }
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(forme[j][i]){
                    grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(Qt::gray);
                }
                else if(grid->GetLabelGrid()[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                    otherBlocksNear = 1;
                }
            }
        }
        if(otherBlocksNear){
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++){
                    if(grid->GetLabelGrid()[j + position[0]][2 - i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                        if(i == 2 || i == 3){
                            otherBlocksNear_down = true;
                        }
                        if(j == 1 || j == 0){
                            otherBlocksNear_left = true;
                        }
                        if(j == 3 || j == 2){
                            otherBlocksNear_right = true;
                        }
                    }
                }
            }
        }
        if((otherBlocksNear_left && otherBlocksNear_right) || otherBlocksNear_down){
            forme = temp;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(forme[j][i]){
                        grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
                    }
                }
            }
            return;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if(otherBlocksNear == 1 && grid->GetLabelGrid()[j + position[0]][3 - i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                    if(j <= 1){
                        position[0] += 1;
                    }
                    else{
                        if(grid->GetLabelGrid()[j - 1 + position[0]][3 - i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                            position[0] -= 1;
                        }
                        else{
                            forme = temp;
                            for(int i = 0; i < 4; i++) {
                                for(int j = 0; j < 4; j++) {
                                    if(forme[j][i]){
                                        grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
                                    }
                                }
                            }
                            return;
                        }
                    }
                }
                forme[j][3 - i] = temp[i][j];
            }
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(forme[j][i]){
                grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
            }
        }
    }
}

void Bloc::RotateCounterClockwise(int *position, GameGrid *grid)
{
    std::array<std::array<int, 4>, 4> temp = forme;
    int otherBlocksNear = false;
    int otherBlocksNear_left = false;
    int otherBlocksNear_right = false;
    int otherBlocksNear_down = true;
    if(lenght == 9){
        if(position[1] > 17){
            return;
        }
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(forme[j][i]){
                    grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(Qt::gray);
                }
                else if(grid->GetLabelGrid()[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                    otherBlocksNear = 1;
                }
            }
        }
        if(otherBlocksNear){
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++){
                    if(grid->GetLabelGrid()[j + position[0]][2 - i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                        if(i == 2 || i == 3){
                            otherBlocksNear_down = true;
                        }
                        if(j == 1 || j == 0){
                            otherBlocksNear_left = true;
                        }
                        if(j == 3 || j == 2){
                            otherBlocksNear_right = true;
                        }
                    }
                }
            }
        }
        if((otherBlocksNear_left && otherBlocksNear_right) || otherBlocksNear_down){
            forme = temp;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(forme[j][i]){
                        grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
                    }
                }
            }
            return;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(otherBlocksNear == 1 && grid->GetLabelGrid()[2 - j + position[0]][i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                    if(2 - j <= 1){
                        position[0] += 1;
                    }
                    else{
                        if(grid->GetLabelGrid()[2 - j - 1 + position[0]][i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                            position[0] -= 1;
                        }
                        else{
                            forme = temp;
                            for(int i = 0; i < 3; i++) {
                                for(int j = 0; j < 3; j++) {
                                    if(forme[j][i]){
                                        grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
                                    }
                                }
                            }
                            return;
                        }
                    }
                }
                forme[2 - j][i] = temp[i][j];
            }
        }
    } else {
        if(position[1] > 17){
            return;
        }
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(forme[j][i]){
                    grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(Qt::gray);
                }
                else if(grid->GetLabelGrid()[i + position[0]][j + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                    otherBlocksNear = 1;
                }
            }
        }
        if(otherBlocksNear){
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++){
                    if(grid->GetLabelGrid()[j + position[0]][2 - i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                        if(i == 3 || i == 2){
                            otherBlocksNear_down = true;
                        }
                        if(j == 1 || j == 0){
                            otherBlocksNear_left = true;
                        }
                        if(j == 3 || j == 2){
                            otherBlocksNear_right = true;
                        }
                    }
                }
            }
        }
        if((otherBlocksNear_left && otherBlocksNear_right) || otherBlocksNear_down){
            forme = temp;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(forme[j][i]){
                        grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
                    }
                }
            }
            return;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if(otherBlocksNear == 1 && grid->GetLabelGrid()[j + position[0]][3 - i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                    if(j <= 1){
                        position[0] += 1;
                    }
                    else{
                        if(grid->GetLabelGrid()[j - 1 + position[0]][3 - i + position[1]]->palette().color(QPalette::Window) != Qt::gray){
                            position[0] -= 1;
                        }
                        else{
                            forme = temp;
                            for(int i = 0; i < 4; i++) {
                                for(int j = 0; j < 4; j++) {
                                    if(forme[j][i]){
                                        grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
                                    }
                                }
                            }
                            return;
                        }
                    }
                }
                forme[j][3 - i] = temp[i][j];
            }
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(forme[j][i]){
                grid->GetLabelGrid()[i + position[0]][j + position[1]]->setPalette(color);
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

bool Bloc::FreeColumn(int columnNumber){
    int count = 0;
    for(int i = 0; i < 4; i++){
        if(forme[i][columnNumber] == 0){
            count += 1;
        }
    }
    return count == 4;
}
