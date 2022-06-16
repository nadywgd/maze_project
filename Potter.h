#ifndef POTTER_H
#define POTTER_H

#include "Moving.h"

// η κλάση Potter κληρονομεί την κλάση Moving
class Potter: public Moving{

    public:
    Potter(const int&, const int&);
    // μέθοδος υπεύθυνση για την κίνηση του παίχτη σύμφωνα με την είσοδο του χρήστη
    bool movePlayer(int &, bool **);
};

#endif