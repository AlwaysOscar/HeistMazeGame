#ifndef TRACKER_H
#define TRACKER_H

#include "position.h"
#include "enemy.h"
#include "ally.h"

// should inherit from Enemy
class Tracker : public Enemy
{
public:
    /** Tracker constructor. Calls Enemy constructor with type 'T'
     * @parameter pos is the initial position.
     * @parameter player is a pointer to the Ally object in the castle */
    Tracker(const Position &pos, char type, const Ally* player) : Enemy(pos, 'T') { this->player = player; }

    /** Moves the Enemy. This function overrides in the Enemy's pure virtual function
     *  moves this Tracker towards the player either in the x or y direction.
     * @parameter move determines the  position to move to. 
     *            Defaults to 'A' for auto */
    void move(const char move = 'A'); 

    /** Gets player's info (Position etc) */
    const Ally *getPlayer() const;          

    /** Gets player's x-coordinate */
    const size_t getPlayerX() const;   

    /** Gets player's y-coordinate */     
    const size_t getPlayerY() const;        

    /** Calculate the shortest path to player aka follow them
     * @parameter xCoord is x-coordinate of Enemy being checked
     * @parameter yCoord is y-coordinate of Enemy being checked
     * @return valid direction for Tracker to either move (1-4) = (N,E,S,W)
     * Note: if x == y coord, randRange will break tie to move either or */
    int calculatePathToPlayer(const size_t &xCoord, const size_t &yCoord);
    
    /** Destructor */
    ~Tracker(){};
    
protected:
private:
    const Ally* player;
};
#endif  // TRACKER_H