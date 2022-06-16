#include "Potter.h"
#include <ncurses.h>

Potter::Potter(const int& input_x, const int& input_y):
Moving(input_x, input_y){}

// μέθοδος υπεύθυνση για την κίνηση του παίχτη σύμφωνα με την είσοδο του χρήστη
bool Potter::movePlayer(int &input, bool **map){

    switch(input) {
        /* Αν πατηθεί το αριστερά βελάκι, γίνεται μετακίνηση του παίχτη προς τα αριστερά
          σε περίπτωση που επιτρέπεται και γίνεται επιστροφή true, αλλιώς επιστροφή false.*/
        case KEY_LEFT:
            if(moveLeft(map))
                return true;
            else 
                return false;
            break;

        /* Αν πατηθεί το δεξιά βελάκι, γίνεται μετακίνηση του παίχτη προς τα δεξιά
          σε περίπτωση που επιτρέπεται και γίνεται επιστροφή true, αλλιώς επιστροφή false.*/
        case KEY_RIGHT:
            if(moveRight(map))
                return true;
            else 
                return false;    
            break;
        /* Αν πατηθεί το πάνω βελάκι, γίνεται μετακίνηση του παίχτη προς τα πάνω
          σε περίπτωση που επιτρέπεται και γίνεται επιστροφή true, αλλιώς επιστροφή false.*/ 
        case KEY_UP:
            if(moveUp(map))
                return true;
            else 
                return false;
        break;
        /* Αν πατηθεί το κάτω βελάκι, γίνεται μετακίνηση του παίχτη προς τα κάτω
          σε περίπτωση που επιτρέπεται και γίνεται επιστροφή true, αλλιώς επιστροφή false.*/
        case KEY_DOWN:
            if(moveDown(map))
                return true;
            else 
                return false;
        break;
        
        /* Σε περίπτωση που πατηθεί το πλήκτρο 'space', ο παίκτης παραμένει ακίνητος
          και επιστρέφεται true σαν να έχει κινηθεί. */
        case ' ':
            return true;

        default:
            return false;
        break;
    }
}