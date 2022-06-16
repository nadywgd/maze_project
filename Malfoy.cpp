#include "Malfoy.h"

Malfoy::Malfoy(const int& input_x, const int& input_y):
Moving(input_x, input_y){}

// αναδρομική συνάρτηση η οποία υπολογίζει το συντομότερο μονοπάτι από ένα σημείο σε ένα άλλο
bool Malfoy::validPath(bool **maze, int srcY, int srcX, int destY, 
int destX, int distance, int &steps, const int &mapHeight, const int &mapWidth) {
    
    // εάν υπάρχει τοίχος, επιστρέφει false 
    if (maze[srcY][srcX] != false)
        return false;

    // εάν έφτασε στον στόχο, αποθηκεύεται και επιστρέφει true
    if (srcY == destY  &&  srcX == destX){
	steps = distance;
	return true;
	}
    
    // όλες οι θέσεις που επισκέπτονται σημειώνονται ως true
    maze[srcY][srcX] = true;

    // κλήση συνάρτησης για κάθε διαθέσιμη κίνηση
    if (validPath(maze, srcY-1, srcX, destY, destX, distance+1, steps, mapHeight, mapWidth))
        return true;
    if (validPath(maze, srcY+1, srcX, destY, destX,distance+1, steps, mapHeight, mapWidth))
        return true;
    if (validPath(maze, srcY, srcX-1, destY, destX, distance+1, steps, mapHeight, mapWidth))
        return true;
    if (validPath(maze, srcY, srcX+1, destY, destX, distance+1, steps, mapHeight, mapWidth))
        return true;

    // αλλιώς, γίνεται επιστροφή false
    return false;
} 

// υπολογισμός όλων των 4 κινήσεων + της πρώτης απόστασης για να επιλεγχθεί η κατεύθυνση
void Malfoy::moveMalfoy(bool  ** map, const int &mapHeight, const int &mapWidth, const int &playerY, const int &playerX){

    // αρχικοποίηση πινάκων για τις αποστάσεις και τις συντεταγμένες των τεσσάρων κινήσεων + και της πρώτης απόστασης
    int distArray[5] = {10000, 10000, 10000, 10000, 10000};
    int diffX[5] = {x-1, x+1, x, x, x};
    int diffY[5] = {y, y, y-1, y+1, y};

    // για κάθε διαθέσιμη κίνηση   
    for (int i=0; i<5; i++){
		// αρχικοποίηση πίνακα
        bool **maze;
		maze = new bool *[mapHeight];
    	for (int j=0; j < mapWidth; j++){
       		maze[j] = new bool[mapWidth];
    	}

    	for (int fx=0; fx < mapHeight; fx++) {
        	for (int fy=0; fy < mapWidth; fy++){
            	maze[fx][fy] = map[fx][fy];
        	}
    	}

        // κλήση συνάρτησης
        validPath(maze, playerY, playerX, diffY[i], diffX[i], 0, distArray[i], mapHeight, mapWidth);
        delete maze; // απελευθέρωση μνήμης
    }

    // Μετακίνηση του Μαλφόη βάσει της μικρότερης απόστασης
    if (distArray[0] == distArray[4]-1)
        moveLeft(map);
    else if (distArray[1] == distArray[4]-1)
        moveRight(map);
    else if (distArray[2] == distArray[4]-1)
        moveUp(map);
    else if (distArray[3] == distArray[4]-1)
        moveDown(map);  
}