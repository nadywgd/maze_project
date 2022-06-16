#ifndef ENTITY_H
#define ENTITY_H

#include <string>

// βασική κλάση Entity που περιέχει τα κύρια στοιχεία κάθε χαρακτήρα
class Entity{

    protected:
    int x,y; // συντεταγμένες
    
    public:
    Entity(const int&, const int&);
    // getters
    int getX();
    int getY();

    // setters
    void setY(const int&);
    void setX(const int&);

    // σχεδιασμός χαρακτήρα 
    void drawEntity(const int&, const int&, const char, int);

};

#endif