#include "ally.h"

/** Moves the Ally based on the pos argument.
 *  This function overrides the Characters class' pure virtual function
 * @parameter move determines the updated position to move to. Moves: [N, S, E, W, P, C] */
void Ally::move(const char move) {   
    size_t xCoord = this->getPosition().x;
    size_t yCoord = this->getPosition().y;

    switch (move) {
    case 'N':
        setYPosition((--(yCoord))); // move up (North 'N')
        break;
    case 'S':
        setYPosition((++(yCoord))); // move down (South 'S')
        break;
    case 'E':
        setXPosition((++(xCoord))); // move right (East 'E')
        break;
    case 'W':
        setXPosition((--(xCoord))); // move left (West 'W')
        break;
    case 'P':                        // Pause
        break;
    case 'C':                        // picks up the scientist
        break;
    default:
        break;
    }
}