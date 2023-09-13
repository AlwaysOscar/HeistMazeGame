#include "enemy.h"

/** Moves the Enemy. This is a pure virtual function which is overrriden in the derived Enemy's
 * @parameter move determines the  position to move to. Should be a pure virtual function,
 *            Defaults to 'A' for auto */
void Enemy::move(char move){};

/** Moves the Enemy. This is a pure virtual function which is overrriden in the derived Enemys
 * @parameter move determines the  position to move to. Defaults to 'A' for auto */
void Enemy::enemyMovRandDir(const Enemy& Enemy) {
    size_t xCoord = Enemy.getPosition().x; 
    size_t yCoord = Enemy.getPosition().y;

    int holdRandomVal = preventEnemyOFB(xCoord, yCoord);

    switch (holdRandomVal) {
    case 1:
        setYPosition((--(yCoord))); // move up (North 'N')
        break;
    case 2:
        setYPosition((++(yCoord))); // move down (South 'S')
        break;
    case 3:
        setXPosition((++(xCoord))); // move right (East 'E')
        break;
    case 4:
        setXPosition((--(xCoord))); // move left (West 'W')
        break;
    default:
        break;
    }
}

/** Utility function to help prevent Enemy random movement from going out of bounds 
 * @parameter xCoord is x-coordinate of Enemy being checked
 * @parameter yCoord is y-coordinate of Enemy being checked
 * @return valid random direction for Enemy to either move (1-4) = (N,E,S,W)
 * Note: invalid movement options will be elminated */
int Enemy::preventEnemyOFB(const size_t &xCoord, const size_t &yCoord) {
    int holdRandomVal;                      // Holds the random generated value to be returned
   
    // Check what movement is not allowed
    bool canMoveUp = (yCoord > 0);
    bool canMoveDown = (yCoord < NUM_OF_ROWS - 1);
    bool canMoveRight = (xCoord < NUM_OF_COLUMNS - 1);
    bool canMoveLeft = (xCoord > 0);

    // Calculate the number of valid directions
    int validDirections = canMoveUp + canMoveDown + canMoveRight + canMoveLeft;
    
    // Generate a random range based of the given scenarios
    if (validDirections == 0) { return -1; } // No valid directions

    int randomDirection = randomRangeChrono(1, validDirections);

    // Determine the direction based on the random number
    if (canMoveUp) {
        randomDirection--;
        if (randomDirection == 0) {return 1;} // Move North
    }
    if (canMoveRight) {
        randomDirection--;
        if (randomDirection == 0) {return 3;} // Move East
    }

    if (canMoveDown) {
        randomDirection--;
        if (randomDirection == 0) {return 2;} // Move South
    }
    if (canMoveLeft) {return 4;}              // Move West

    return -1;                                // Default return value (error case)

}

/** Generates a random Number between a given range, using high-resolution clock for seeding
 * @parameter start is the start of the range from. 
 * @parameter end is the end of the range to. */    
int Enemy::randomRangeChrono(const int start, const int end) {
    auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    static std::default_random_engine rndEng(seed);
    std::uniform_int_distribution<int> uniformDist(start, end);
    return uniformDist(rndEng);
}
