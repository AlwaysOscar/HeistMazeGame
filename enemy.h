#ifndef ENEMY_H
#define ENEMY_H

#include <random>
#include <chrono>
#include "characters.h"
#include "position.h"
//#include "customExceptions.h"
#include "constants.h"

// should inherit from Characters but be an abstract class
class Enemy : public Characters
{
public:
    /** Enemy constructor. Calls Characters constructor
     * @parameter pos is the initial position
     * @parameter type is the type of Characters */
    Enemy(const Position &pos, char type) : Characters(pos, type) {}

    /** Moves the Enemy. This is a pure virtual function which is overrriden in the derived Enemys
     * @parameter move determines the  position to move to. Defaults to 'A' for auto */
    void move(char move = 'A');

    /** Virtual Destructor */
    ~Enemy(){};

    /** Moves the Enemy position in random direction
     * @parameter Enemy is the Enemy object position being changed */
    void enemyMovRandDir(const Enemy& Enemy);    

    /** Utility function to help prevent Enemy random movement from going out of bounds 
     * @parameter xCoord is x-coordinate of Enemy being checked
     * @parameter yCoord is y-coordinate of Enemy being checked
     * @return valid random direction for Enemy to either move (1-4) = (N,E,S,W)
     * Note: invalid movement options will be elminated */
    int preventEnemyOFB(const size_t &xCoord, const size_t &yCoord);
    
    /** Generates a random Number between a given range, using high-resolution clock for seeding
     * @parameter start is the start of the range from. 
     * @parameter end is the end of the range to. */    
    int randomRangeChrono(const int start, const int end);

protected:
private:
};
#endif  // ENEMY_H