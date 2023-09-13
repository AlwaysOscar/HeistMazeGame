#include "scout.h"

/** Moves the Scout Enemy type, overrides Enemy's pure virtual move function.
     *  this Scout moves in a random direction after every player move.
     * @parameter move determines the  position to move to. 
     *            Defaults to 'A' for auto */
void Scout::move(const char move) { enemyMovRandDir(*this); }