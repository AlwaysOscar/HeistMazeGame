#include "characters.h"

// Setters
void Characters::setPosition(size_t x, size_t y) {
    this->pos->x = x;
    this->pos->y = y;
}
void Characters::setXPosition(size_t x) { this->pos->x = x; }
void Characters::setYPosition(size_t y) { this->pos->y = y; }

/** Gets the type of the character [S, W, T, P, L]
 * @return the type of the Characters */
char Characters::getType() const { return (this->type); }

/** Gets the current position of the Characters
 * @return position. */
Position Characters::getPosition() const { return (*(this->pos)); }

/** Equality operator
 * @parameter other the other character object
 * @return true if this object has the same position as the other and false otherwise */
bool Characters::operator==(const Characters &other) const {
    if (((this->pos->x) == (other.getPosition().x)) && ((this->pos->y) == (other.getPosition().y)))
        return true;
    return false;
}

/** Inequality operator
 * @parameter other the other character object
 * @return false if this object has the same position as the other and true otherwise */
bool Characters::operator!=(const Characters &other) const {
    if (((this->pos->x) == (other.getPosition().x)) && ((this->pos->y) == (other.getPosition().y)))
        return false;
    return true;
}
