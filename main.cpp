#include "Engine.h"

int main(int argc, char **argv){


    // έλεγχος ορθότητας 
    if (argc != 2){
        std::cout << "Παρακαλώ εισάγετε σωστό αριθμό ορισμάτων.\n";
        return 0;
    }

    // Δημιουργία αντικειμένου Engine για τη λειτουργία του παιχνιδιού
    Engine eng;

    // μέθοδος έναρξης παιχνδιού 
    eng.initGame(argv[1]);

}