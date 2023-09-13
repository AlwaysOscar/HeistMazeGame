#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "position.h"

// The base class of Enemy and Ally and is abstract
class Characters
{
public:
    /** Characters object. the base class for enemy and ally
     * @parameter pos. the initial position
     * @parameter type. the type of character */
    Characters(const Position& pos, char t) {
        this->pos = new Position(pos);
        type = t;
    }

    // setters
    void setPosition(size_t x, size_t y);
    void setXPosition(size_t x);
    void setYPosition(size_t y);

    /** Gets the type of the character [S, W, T, P, L]
     * @return the type of the Characters */
    char getType() const;

    /** Gets the current position of the Characters
     * @return position. */
    Position getPosition() const;

    /** Equality operator
     * @parameter other the other character object
     * @return true if this object has the same position as the other and false otherwise */
    bool operator==(const Characters& other) const;

    /** Inequality operator
     * @parameter other the other character object
     * @return false if this object has the same position as the other and true otherwise */
    bool operator!=(const Characters& other) const;

    /** Moves the Characters from the current position to pos. This is a pure virtual function
     * @parameter move determines the direction to move. The default value is 'A' for auto  */
    virtual void move(char move = 'A') = 0; 
    
    /** Virtual Destructor */
    ~Characters() { delete this->pos; }    

protected:
    Position* pos;
    char type;
private:
};
#endif  // CHARACTERS_H