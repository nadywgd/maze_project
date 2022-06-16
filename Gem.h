# ifndef GEM_H
#define GEM_H

#include "Entity.h"

// η κλάση Gem κληρoνομεί την κλάση Entity
class Gem:public Entity{

    public:
    Gem(const int&, const int&); // κατασκευαστής
};

#endif