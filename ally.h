#ifndef ALLY_H
#define ALLY_H

#include "characters.h"
#include "position.h"

// should inherit from Characters
class Ally : public Characters
{
public:
    /** Ally constructor. Calls Characters constructor  
     * @parameter pos is the initial position. 
     * @parameter type is the type of Characters. */
    Ally(const Position& pos) : Characters(pos, 'L'){};

    /** Moves the Ally based on the pos argument. 
     *  This function overrides the Characters class' pure virtual function
     * @parameter move determines the updated position to move to. Moves: [N, S, E, W, P, C] */
    void move(const char move);

    /** Destructor */
    ~Ally(){};
    
protected:
private:
};
#endif  // ALLY_H