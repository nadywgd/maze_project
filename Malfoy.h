#ifndef MALFOY_H
#define MALFOY_H

#include "Moving.h"

//Η κλάση Malfoy κληρονομεί την κλάση Moving
class Malfoy: public Moving{

    public:
    Malfoy(const int&, const int&);
    // αναδρομική συνάρτηση η οποία υπολογίζει το συντομότερο μονοπάτι από ένα σημείο σε ένα άλλο
    bool validPath(bool **, int, int, int, int, int, int&, const int&, const int&);
    //συνάρτηση που μετακινεί τον Μαλφόη σύμφωνα με το συντομότερο μονοπάτι το οποίο υπολογίζεται
    // χρησιμοποιώντας τη συνάρτηση validPath
    void moveMalfoy(bool **, const int &, const int &, const int &, const int &);
};

#endif