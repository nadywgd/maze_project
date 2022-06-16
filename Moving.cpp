#include "Moving.h"
#include <string.h>
#include <iostream>

Moving::Moving(const int& input_x, const int& input_y):
Entity(input_x, input_y){}

/* συναρτήσεις που μετακινούν τον χαρακτήρα σε μια κατεύθυνση
    και επιστρέφουν true εάν η κίνηση είναι έγκυρη, αλλιώς false. */
bool Moving::moveUp(bool **map){
    if (!map[y-1][x]){
        y--;
        return true;
    }
    else
        return false; 
}

bool Moving::moveDown(bool **map){
    if (!map[y+1][x]){
        y++;
        return true;
    }
    else
        return false;
}

bool Moving::moveLeft(bool **map){
    if (!map[y][x-1]){
        x--;   
        return true;
    }
    else
        return false;

}

bool Moving::moveRight(bool **map){
    if (!map[y][x+1]){
        x++;
        return true;
    }
    else
        return false;

}
