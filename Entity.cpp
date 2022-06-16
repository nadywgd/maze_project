#include "Entity.h"
#include <ncurses.h>

Entity::Entity(const int& input_x, const int& input_y){

    x = input_x;
    y = input_y;
}

//getters
int Entity::getX(){
    return x;
}

int Entity::getY(){
    return y;
}

// setters
void Entity::setX(const int& input_x){
    x=input_x;
}

void Entity::setY(const int& input_y){
    y=input_y;
}

// σχεδιασμός χαρακτήρα
void Entity::drawEntity(const int& x, const int& y, const char ch, int color){
    
    attron(COLOR_PAIR(color));
    mvaddch(y, x , ch);
    attroff(COLOR_PAIR(color));
}
