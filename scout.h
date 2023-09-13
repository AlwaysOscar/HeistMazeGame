#ifndef SCOUT_H
#define SCOUT_H

#include "characters.h"
#include "position.h"
#include "enemy.h"

// should inherit from Enemy
class Scout : public Enemy
{
public:
    /** Scout constructor. Calls Enemy constructor with type 'S'
    * @parameter pos is the initial position.*/
    Scout(const Position &pos, char type) : Enemy(pos, 'S') {}

    /** Moves the Scout Enemy type, overrides Enemy's pure virtual move function.
     *  this Enemy moves in a random direction after every player move.
     * @parameter move determines the  position to move to. 
     *            Defaults to 'A' for auto */
    void move(const char move = 'A');

    /** Destructor */
    ~Scout(){};
    
protected:
private:
};
#endif // SCOUT_H