/**
 * @file Bloc.cpp
 * @brief This file implements the functions for the Bloc class
 * @version 0.1
 * 
 */
#include "Bloc.h"

/**
 * @brief This function rotates a Bloc pieace 90 degrees clockwise
 * 
 * @param position The position [x, y] of the current falling Bloc piece
 * @param grid A pointer to the game Grid object
 */
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
                forme[j][i] = temp[i][j];
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

/**
 * @brief This function rotates a Bloc pieace 90 degrees clockwise
 * 
 * @param position The position [x, y] of the current falling Bloc piece
 * @param grid A pointer to the game Grid object
 */
void Bloc::RotateCounterClockwise(int *position, GameGrid *grid)
{
    std::array<std::array<int, 4>, 4> temp = forme;
    int otherBlocksNear = false;
    int otherBlocksNear_left = false;
    int otherBlocksNear_right = false;
    int otherBlocksNear_down = false;
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
                forme[j][i] = temp[i][j];
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

/**
 * @brief This function returns the QColor value of a Bloc piece
 * 
 * @return QColor 
 */
QColor Bloc::GetColor() const
{
    return color;
}

/**
 * @brief This function returns the "length" of the Bloc piece. This corresponds to the matrix size necessary for representing the piece.
 * 
 * @return int 
 */
int Bloc::GetLenght() const {
    return lenght;
}

/**
 * @brief This function returns an int array that represents the shape of the Bloc piece.
 * 
 * @return std::array<std::array<int, 4>, 4> 
 */
std::array<std::array<int, 4>, 4> Bloc::GetForme() const
{
    return forme;
}

/**
 * @brief This function checks if a specific column in the Bloc piece matrix is free (only 0's).
 * 
 * @param columnNumber The column to be checked.
 * @return true
 * @return false 
 */
bool Bloc::FreeColumn(int columnNumber){
    int count = 0;
    for(int i = 0; i < 4; i++){
        if(forme[i][columnNumber] == 0){
            count += 1;
        }
    }
    return count == 4;
}
