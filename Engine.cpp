#include "Engine.h"
#include "Potter.h"
#include "Malfoy.h"
#include "Gem.h"
#include <ncurses.h>

#define POTTER_COLOR 1
#define MALFOY_COLOR 2
#define GEM_COLOR 3
#define WALL_COLOR 4
#define PASSAGE_COLOR 5
#define COLOR_ORANGE 3
#define POTTER_SYMBOL 'M'
#define MALFOY_SYMBOL 'L'
#define GEM_SYMBOL 'G'
#define WALL_SYMBOL '*'
#define PASSAGE_SYMBOL '.'


Engine::Engine(){
    setup();
}

Engine::~Engine(){
    if (map != nullptr)
        delete[] map;
    tearDown();
}


// συνάρτηση για την εφαρμογή χρωμάτων
void Engine::initColors(){
    start_color();
    init_color(COLOR_ORANGE, 1000, 600, 0);
    init_pair(POTTER_COLOR, COLOR_ORANGE, COLOR_BLACK);
    init_pair(MALFOY_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(GEM_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(PASSAGE_COLOR, COLOR_CYAN, COLOR_BLACK);
    init_pair(WALL_COLOR, COLOR_MAGENTA, COLOR_BLACK);

    clear();
}

// υπολογισμός τυχαίων συντεταγμένων
int* Engine::randCoords(){

    int * coords = new int[2];
    int randX, randY;
    do{
        randX = (rand() % width);
        randY = (rand() % height);
    } while(movingMap[randY][randX]);

    coords[0] = randX;
    coords[1] = randY;
    return coords;    
}

// μέθοδος έναρξης παιχνιδιού
void Engine::initGame(char *mapName){

    // έλεγχος ύπαρξης αρχείου χάρτη

    try{
        std::ifstream mapFile(mapName);

            if(!mapFile) throw "Εμφανίστηκε πρόβλημα κατά το άνοιγμα του χάρτη.";

    } catch(const char* cstr){

            endwin();
            std::cerr << cstr << std::endl;        
            exit(1);
    }   

    srand(time(NULL)); // γεννήτρια τυχαίων αριθμών
    int *rCoords; // πίνακας τυχαίων συντεταγμένων

    // άνοιγμα αρχείου χάρτη
    std::ifstream mapDimensions(mapName);
    std::ifstream mapFile(mapName);

    findMapDimensions(mapDimensions);
    mapDimensions.close();
    mapInitialization(height, width, mapFile);
    mapFile.close();

    int counter = 0; // μετρητής βημάτων
    const int offsetX = 10, offsetY = 5; // μετατόπιση σχεδιασμού του χάρτη
    bool moveFlag = false; // μεταβλητή ελέγχου κίνησης για τον Ποτερίδη
    float perimeter = (width*height)/2; // μέσος όρος περίμετρου του χάρτη


    rCoords = randCoords(); // υπολογισμός τυχαίων συντεταγμένων
    Potter mpampis(rCoords[0], rCoords[1]); // δημιουργία χαρακτήρα Ποτερίδη
    setPos(rCoords[1], rCoords[0]); // δέσμευση θέσης  
    delete rCoords; 

    rCoords = randCoords(); // υπολογισμός τυχαίων συντεταγμένων
    Malfoy malfoy(rCoords[0], rCoords[1]); // δημιουργία χαρακτήρα Μαλφόη
    setPos(rCoords[1], rCoords[0]); // δέσμευση θέσης
    delete rCoords;

    rCoords = randCoords(); // υπολογισμός τυχαίων συντεταγμένων
    Gem gem(rCoords[0], rCoords[1]); // δημιουργία μαγικού πετραδιού
    setPos(rCoords[1], rCoords[0]); // δέσμευση θέσης
    delete rCoords;
    
    // απελευθέρωση θέσεων Ποττερίδη και Μαλφόη
    freePos(mpampis.getY(), mpampis.getX(), offsetY, offsetX);
    freePos(malfoy.getY(), malfoy.getX(), offsetY, offsetX);

    // εφαρμογή χρωμάτων
    initColors();
    
    // σχεδιασμός χάρτη
    for (int fx=0; fx < height; fx++) {
        for (int fy=0; fy < width; fy++){
            if (map[fx][fy]){
                attron(COLOR_PAIR(WALL_COLOR));
                mvaddch(fx+offsetY, fy+offsetX, WALL_SYMBOL);
                attroff(COLOR_PAIR(WALL_COLOR));
            }
            else{
                attron(COLOR_PAIR(PASSAGE_COLOR));
                mvaddch(fx+offsetY, fy+offsetX, PASSAGE_SYMBOL);
                attroff(COLOR_PAIR(PASSAGE_COLOR));
            }
        }
    }

    while(!isDone()){
      

        /* σε περίπτωση που ο παίχτης κινήθηκε και ο μετρητής βημάτων έχει φτάσει ένα συγκεκριμένο όριο,
           τότε μετατόποισε το πετράδι σε τυχαίες συντεταγμένες */
        if (moveFlag && counter > (height+width)/2*10){
         
            rCoords = randCoords(); // υπολογισμός νέας θέσης
            freePos(gem.getY(), gem.getX(), offsetY, offsetX); // αποδέσμευση θέσης
            gem.setY(rCoords[1]); // όρισμα συντεταγμένης y
            gem.setX(rCoords[0]); // όρισμα συντεταγμένης x
            setPos(rCoords[1], rCoords[0]);  // δέσμευση νέας θέσης
            counter = 0; // μηδενισμός μετρητή 
            delete rCoords;
        }

        // σχεδιασμός μαγικού πετραδιού
        gem.drawEntity(gem.getX() + offsetX, gem.getY() + offsetY, GEM_SYMBOL, GEM_COLOR); 
        // σχεδιασμός Ποτερίδη
        mpampis.drawEntity(mpampis.getX() + offsetX, mpampis.getY() + offsetY, POTTER_SYMBOL, POTTER_COLOR); 
        // σχεδιασμός Μαλφόη
        malfoy.drawEntity(malfoy.getX() + offsetX, malfoy.getY() + offsetY, MALFOY_SYMBOL, MALFOY_COLOR); 

        //έλεγχος εισόδου από το πληκτρολόγιο
        int input = getKey();

        // Σε περίπτωση που ο χρήστης πατήσει το κουμπί 'ESC', το παιχνίδι τερματίζει
        if( input == 27) {
            quit();
        }

        // μετακίνηση του Ποτερίδη σε περίπτωση που ο χρήστης έδωσε έγκυρη κίνηση
        freePos(mpampis.getY(), mpampis.getX(), offsetY, offsetX); // αποδέσμευση θέσης
        moveFlag = mpampis.movePlayer(input, map); // μετακίνηση του Ποτερίδη βάσει της εισόδου 
        setPos(mpampis.getY(), mpampis.getX()); // δέσμευση θέσης

        // μετακίνηση του Μαλφόη σε περίπτωση που μετακινηθεί ο Ποτερίδη ή ο χρήστης πατήσει το πλήκτρο 'space'
        if(moveFlag){

            freePos(malfoy.getY(), malfoy.getX(), offsetY, offsetX); // αποδέσμευση θέσης
            malfoy.moveMalfoy(map, height, width, gem.getY(), gem.getX()); // μετακίνηση του Μαλφόη προς το μαγικό πετράδι
            setPos(malfoy.getY(), malfoy.getX()); // δέσμευση θέσης
            // προσαύξηση του μετρητή κίνησης με έναν τυχαίο αριθμό στο εύρος 1-20
            counter += (rand() % 20);
        }

        // έλεγχος τερματισμού παιχνιδιού
        int check = endGame(mpampis.getY(), mpampis.getX(), 
        malfoy.getY(), malfoy.getX(), gem.getY(), gem.getX());

        // σε περίπτωση που φτάσει ο Ποτερίδη στο μαγικό πετράδι, η οθόνη καθαρίζεται και εμφανίζεται το μήνυμα νίκης
        if (check == 1) {
       
            quit();
            endwin();
            std::cout << "Συγχαριτήρια, ΚΕΡΔΙΣΕΣ!!\n";

        // αν φτάσει πρώτος ο Μαλφόη στο μαγικό πετράδι, η οθόνη καθαρίζεται και εμφανίζεται το μήνυμα ήττας
        } else if (check == 2) {
 
            quit();
            endwin();
            std::cout << "Ο Λουκάς Μαλφόης έφτασε πρώτος στο πετράδι, ΈΧΑΣΕΣ!\n";
        }

        endDraw(); // τέλος σχεδιασμού
    }
}

// Υπολογισμός διαστάσεων χάρτη
void Engine::findMapDimensions(std::ifstream &mapDimensions){
    std::string line;
    getline(mapDimensions, line);
    height++;
    width = line.length();
    while (getline(mapDimensions, line)){
        height++;
    }
}

// μέθοδος αρχικοποίησης χάρτη
void Engine::mapInitialization(const int &mapHeight,const int &mapWidth, std::ifstream &file){
    map = new bool *[mapHeight];
    movingMap = new bool *[mapHeight];
    for (int i=0; i < mapHeight; i++){
        map[i] = new bool[mapWidth];
        movingMap[i] = new bool[mapWidth];
        
    }

     // ορισμός όλων των θέσεων του χάρτη σε false
    for(int i=0; i<mapHeight; i++) {          
        for (int j=0; j <mapWidth; j++) {
            map[i][j] = false;
            movingMap[i][j] = false;
            
        }
    } 

    // όρισμος όλων των θέσεων όπου ο χάρτης περιέχει τον χαρακτήρα '*' σε true 
    char byte;
    for(int i=0; i<=mapHeight; i++){              
        for (int j=0; j <=mapWidth; j++){
            file.get(byte);
            if (file.eof()){
                break;
            }
            else if (byte == '*'){
                map[i][j] = true;
                movingMap[i][j] = true;
            }
            else if (byte == '\n'){
                break;
            }        
        }      
    }
}

// συνάρτηση ελέγχου λήξης παιχνιδιού
int Engine::endGame(const int &playerY, const int &playerX, const int &malfoyY, const int &malfoyX,const int &gemY, const int &gemX){

    if(playerY == gemY && playerX == gemX)
        return 1;

    else if(malfoyY == gemY && malfoyX == gemX)
        return 2;    

    else
        return 0;
}

// setter για τον πίνακα ελεύθερων θέσεων
void Engine::freePos(const int &y, const int &x, const int& offsetY, const int& offsetX){

    movingMap[y][x] = false;
    attron(COLOR_PAIR(PASSAGE_COLOR));
    mvaddch(y+offsetY, x+offsetX,'.');
    attroff(COLOR_PAIR(PASSAGE_COLOR));
}

// setter για τον πίνακα ελεύθερων θέσεων
void Engine::setPos(const int &y, const int &x){

    movingMap[y][x] = true;
}


// wrappers για την βιβλιοθήκη ncurses
void Engine::setup(){
    initscr();
    curs_set(0);
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

void Engine::tearDown(){
    endwin();
}

int Engine::getKey(){
    return getch();
}


void Engine::startDraw(){
    clear();
}
    
void Engine::endDraw(){
    refresh();
}

bool Engine::isDone(){
    return m_done;
}

void Engine::quit(){
    m_done = true;
}