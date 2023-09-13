#include "tracker.h"

/** Tracker constructor. Calls Enemy constructor with type 'T'
 * 50% chance of moving this Enemy in direction of player after every player move.
 * @parameter pos is the initial position.
 * @parameter player is a pointer to the Ally object in the castle */
void Tracker::move(const char move) {
    /* generates # from range 1-10, if (1-5) return thus 50% chance of move */
    int tempRandVal = randomRangeChrono(1, 10);
    if ((tempRandVal == 1) || (tempRandVal == 2) || (tempRandVal == 3) || (tempRandVal == 4) || (tempRandVal == 5)) 
    { return; }

    size_t xCoord = this->getPosition().x; 
    size_t yCoord = this->getPosition().y;
    int moveDecision = calculatePathToPlayer(xCoord, yCoord);

    switch (moveDecision) {
    case 1:
        setYPosition((--(yCoord))); // move up (North 'N')
        break;
    case 2:
        setYPosition((++(yCoord))); // move down (South 'S')
        break;
    case 3:
        setXPosition((++(xCoord))); // move right (East 'E')
        break;
    case 4:
        setXPosition((--(xCoord))); // move left (West 'W')
        break;
    default:
        break;
    }
}

/** Gets player's info (Position etc) */
const Ally *Tracker::getPlayer() const { return (this->player); }               // Gets player's info (Position etc)

/** Gets player's x-coordinate */
const size_t Tracker::getPlayerX() const { return (this->player->getPosition().x); }  // Gets player's x-coordinate

/** Gets player's y-coordinate */
const size_t Tracker::getPlayerY() const { return (this->player->getPosition().y); }  // Gets player's y-coordinate

/** Calculate the shortest path to player aka follow them
 * @parameter xCoord is x-coordinate of Enemy being checked
 * @parameter yCoord is y-coordinate of Enemy being checked
 * @return valid direction for Tracker to either move (1-4) = (N,E,S,W)
 * Note: if x == y coord, randRange will break tie to move either or */
int Tracker::calculatePathToPlayer(const size_t &xCoord, const size_t &yCoord) {
    int moveDecision;

    // Calculate the differences in x and y coordinates, take absolute value if (-)value occur
    int xDiff = abs(static_cast<int>(xCoord - this->getPlayerX()));
    int yDiff = abs(static_cast<int>(yCoord - this->getPlayerY()));

    // Calculate if the the player is to the right of the aggressor
    bool isPlayerToRight = (xCoord < this->getPlayerX());

    // Calculate if the the player is to the above the aggressor
    bool isPlayerAbove = (yCoord > this->getPlayerY());

    if (((xDiff < yDiff) && (xDiff != 0)) || (yDiff == 0)) {    // x closer, move horizontally
        if (isPlayerToRight == true) { moveDecision = 3; }      // Move East
        else { moveDecision = 4; }                              // Move West
    } 

    else {                                                      // y closer, move vertically
        if (isPlayerAbove) { moveDecision = 1; }                // Move North
        else { moveDecision = 2; }                              // Move South
    }

    return moveDecision;
}