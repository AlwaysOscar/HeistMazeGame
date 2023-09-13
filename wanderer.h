#ifndef WANDERER_H
#define WANDERER_H

#include "characters.h"
#include "position.h"
#include "enemy.h"

// should inherit from Enemy
class Wanderer : public Enemy
{
public:
    /** Wanderer constructor. Calls Enemy constructor with type 'W'
     * @parameter pos is the initial position.*/
    Wanderer(const Position &pos, char type) : Enemy(pos, 'W'){};

    /** Moves the Wanderer Enemy type, overrides Enemy's pure virtual move function.
     *  20% chance of moving this Wanderer in a random direction after every player move.
     * @parameter move determines the  position to move to.
     *            Defaults to 'A' for auto
     */
    void move(const char move = 'A');

    /** Destructor */
    ~Wanderer(){};

protected:
private:
};
#endif  // WANDERER_H