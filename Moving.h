#ifndef MOVING_H
#define MOVING_H

#include "Entity.h"

// η κλάση Moving κληρονομεί την κλάση Entity
class Moving: public Entity{

    public:
    Moving(const int&, const int&); // κατασκευαστής

    /* συναρτήσεις που μετακινούν τον χαρακτήρα σε μια κατεύθυνση
       και επιστρέφουν true εάν η κίνηση είναι έγκυρη, αλλιώς false. */
    bool moveUp(bool **);
    bool moveDown(bool **);
    bool moveLeft(bool **);
    bool moveRight(bool **);


};

#endif