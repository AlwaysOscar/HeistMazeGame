#ifndef POSITION_H
#define POSITION_H

#include <stddef.h>

struct Position
{
    size_t x;
    size_t y;

    Position() : x{0}, y{0} {}
    Position(size_t x, size_t y) : x{x}, y{y} {}
    Position(const Position &other) : x{other.x}, y{other.y} {}

    /** Equality operator
     * @parameter other the other Position object
     * @return true if this Position is the same as another Position and false otherwise */
    bool operator==(const Position &other) const {
        if (((this->x) == (other.x)) && ((this->y) == (other.y))) { return true; }
        else { return false; }
    }

    /** Inequality operator
     * @parameter other the other Position object
     * @return false if this Position is the same as another Position and true otherwise */
    bool operator!=(const Position &other) const {
        if (((this->x) == (other.x)) && ((this->y) == (other.y))) { return false; }
        else { return true; }
    }
};
#endif  // POSITION_H