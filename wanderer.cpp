#include "wanderer.h"

/** Moves the Wanderer Enemy type, overrides Enemy's pure virtual move function.
 * 20% chance of moving this Wanderer in a random direction after every player move.
 * @parameter move determines the  position to move to.
 * Defaults to 'A' for auto */
void Wanderer::move(const char move) {
    /* generates # from range 1-10 if (1 or 2) thus 20% chance of move */
    int tempRandVal = randomRangeChrono(1, 10);
    if ((tempRandVal == 1) || (tempRandVal == 2)) { enemyMovRandDir(*this); }
}
