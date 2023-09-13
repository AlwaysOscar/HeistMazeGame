// iostream is only used for the operator<< function.
// Do not print anything directly to cout from this or any other class
#ifndef GAME_H
#define GAME_H

#include <iostream> // For stream insertion operator
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>
#include <random>
#include <chrono>
//#include <memory>   // For std::make_unique

#include "ally.h"
#include "enemy.h"
#include "scout.h"
#include "wanderer.h"
#include "tracker.h"
#include "constants.h"
#include "customExceptions.h"

// this class does not provide UI nor does it contain main.
class Game
{
    /** stream insertion operator overload */
    friend std::ostream &operator<<(std::ostream &os, const Game &game);

public:
    /** Game constructor. Initializes the Game */
    Game() { initializeAll(); }

    /** move the position of the player
     @ parameter move the direction in which the player must move: must be a valid move
     @ throws invalid_argument exception if move is invalid */
    void move(char move);

    /** Game destructor. Deletes all heap based objects 
     * in the reverse order of their creation or allocation.*/
    ~Game() {
        delete causeOfLost;
        delete playerStatus;
        delete isCarryingLoot;
        delete loot;
        delete player;
        // if Game class out of scope/ destroyed, all ally objects automatically deleted
    }

    /* Setters */
    void setIsCarryingLoot(const bool &b);
    void setPlayerStatus(const char &status);
    void setCauseOfLost(const std::string &cause);
    void setCauseOfLost(const char &cause);

    /* Getters */
    Ally *getLoot() const;
    Ally *getPlayer() const;
    std::vector<Enemy *> getEnemies() const;
    //std::vector<std::unique_ptr<Enemy>> getEnemies();
    bool getIsCarryingLoot() const;
    char getPlayerStatus() const;
    std::string getCauseOfLost() const;

    /** initialize player, loot, and enemies with generated position */
    void initializeAll();

    /** initialize loot class member */
    void initializeLoot();

    /** initialize enemies vector class member */
    void initializeEnemies();

    /** call the move function for each respective type of all enemies */
    void allEnemiesMove();

    /** Determine which enemy type are at this postion.
     * @parameter currentCellPos is the current cell position (x,y) beening checked.
     * @return a string of 3 characters representing a wanderer 'W', scout 'S', or tracker 'T'.
     * if either some or all are missing a empty char ' ' holds it place. 
     * Note multiple of same type in the cell is represented by 1 char */
    std::string whichEnemyHere(const Position &currentCellPos) const;

    /** check if player and loot are on the same position
     * @return true if player position == loot position, else false */
    bool isAbleToCarry() const;

    /** generate a random postition within bounds of the grid and 1 cell away from player
     * @return a randomly generate postion object */
    Position generateRandomPostition();

    /** Generates a random Number between a given range, using high-resolution clock for seeding
     * @parameter start is the start of the range from. 
     * @parameter end is the end of the range to. */    
    int randomRangeChrono(const int start, const int end);

private:
    std::vector<Enemy *> enemies;
    //std::vector<std::unique_ptr<Enemy>> enemies;
    Ally *player;
    Ally *loot;
    bool *isCarryingLoot;
    char *playerStatus;
    std::string *causeOfLost;
};
#endif  // GAME_H