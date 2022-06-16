#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <fstream>
#include <string>

class Engine{

    private:
    unsigned int width=0, height=0;
    bool **map=nullptr;
    bool **movingMap=nullptr;
    bool m_done;


    public:
    Engine();
    ~Engine();

    void initColors(); // συνάρτηση για την εφαρμογή χρωμάτων 
    int* randCoords(); // συνάρτηση υπολογισμού τυχαίων συντεταγμένων
    void initGame(char*); // μέθοδος έναρξης παιχνιδιού
    void findMapDimensions(std::ifstream &); // υπολογισμός διαστάσεων χάρτη
    void mapInitialization(const int &,const int &, std:: ifstream &); // μέθοδος αρχικοποίησης χάρτη
    void freePos(const int &, const int &, const int &, const int &); // αποδέσμευση  θέσης στον πίνακα ελεύθερων θέσεων
    void setPos(const int &, const int &); // δέσμευση θέσης στον πίνακα ελεύθερων θέσεων 
    // συνάρτηση ελέγχου λήξης παιχνιδιού
    int endGame(const int &, const int &, const int &, const int &,const int &, const int &);  

    // wrappers για την βιβλιοθήκη ncurses
    void setup();
    void tearDown();
    int getKey();
    void startDraw();
    void endDraw();
    bool isDone();
    void quit();
};
#endif