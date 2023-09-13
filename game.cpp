#include "game.h"

/** move the position of the player
 * @ parameter move the direction in which the player must move: must be a valid move
 * @ throws invalid_argument exception if move is invalid */
void Game::move(char move) {
    size_t xCoord = this->getPlayer()->getPosition().x; 
    size_t yCoord = this->getPlayer()->getPosition().y;

    switch (move) {
    case 'N':
        if(yCoord == 0) { throw InvalidMoveException(); }
        else
            this->getPlayer()->setYPosition((--(yCoord))); // move up (North 'N')
        break;
    case 'S':
        if(yCoord == (NUM_OF_ROWS-1)) { throw InvalidMoveException(); }
        else
            this->getPlayer()->setYPosition((++(yCoord))); // move down (South 'S')
        break;
    case 'E':
        if(xCoord == (NUM_OF_COLUMNS-1)) { throw InvalidMoveException(); }
        else
            this->getPlayer()->setXPosition((++(xCoord)));  // move right (East 'E')
        break;
    case 'W':
        if(xCoord == 0) { throw InvalidMoveException(); }
        else
            this->getPlayer()->setXPosition((--(xCoord)));  // move left (West 'W')
        break;
    case 'P':                                               // Pause
        break;
    case 'C':                                               // Picks up the loot
        if (isAbleToCarry() == true) { setIsCarryingLoot(true); }
        break;
    default:
        break;
    }
}

/* Setters */
void Game::setIsCarryingLoot(const bool &b) { (*(this->isCarryingLoot)) = b; }
void Game::setPlayerStatus(const char &status) { (*(this->playerStatus)) = status; }
void Game::setCauseOfLost(const std::string &cause) { (*(this->causeOfLost)) = cause; }
void Game::setCauseOfLost(const char &cause) {
    switch (cause) {
    case 'T':
        (*(this->causeOfLost)) = "Tracker";
        break;
    case 'W':
        (*(this->causeOfLost)) = "Wanderer";
        break;
    case 'S':
        (*(this->causeOfLost)) = "Scout";
        break;
    default:
        (*(this->causeOfLost)) = "Unknown";
        break;
    }
}

/* Getters */
Ally *Game::getLoot() const{ return (this->loot); }
Ally *Game::getPlayer() const{ return (this->player); }
std::vector<Enemy *> Game::getEnemies() const{ return (this->enemies); }
//std::vector<std::unique_ptr<Enemy>> Game::getEnemies() { return (this->enemies); }
bool Game::getIsCarryingLoot() const{ return *(this->isCarryingLoot); }
char Game::getPlayerStatus() const { return *(this->playerStatus); };
std::string Game::getCauseOfLost() const { return *(this->causeOfLost); }

/** initialize player, loot, and enemies with generated position */
void Game::initializeAll() {
    this->player = new Ally(Position());                    // initialize player
    initializeLoot();
    initializeEnemies();
    this->isCarryingLoot = new bool;                        // initialize isCarryingLoot to false at start
    setIsCarryingLoot(false);
    this->playerStatus = new char;                          // initialize playerStatus to playing 'p' at start
    setPlayerStatus('P');
    this->causeOfLost = new std::string;                    // initialize causeOfLost to "Unknown" at start
    setCauseOfLost("Unknown");
}

/** initialize loot class member */
void Game::initializeLoot() {
    this->loot = new Ally(Position());

    // The loot is located in one of the 4 centrally located rooms: (3,4),(3,5),(4,4),&(4,5)
    //size_t xCoord = randomRangeChrono(3, 4);
    //size_t yCoord = randomRangeChrono(4, 5);

    // The LOOT is located at the bottom right of the grid
    size_t xCoord = (NUM_OF_COLUMNS-1);
    size_t yCoord = (NUM_OF_ROWS-1);

    loot->setPosition(xCoord, yCoord);
}

/** initialize enemies vector class member */
void Game::initializeEnemies() {
    for (int i = 0; i < NUM_OF_SCOUTS; i++) { enemies.push_back(new Scout(generateRandomPostition(), 'S')); }
    for (int i = 0; i < NUM_OF_WANDERERS; i++) { enemies.push_back(new Wanderer(generateRandomPostition(), 'W')); }
    for (int i = 0; i < NUM_OF_TRACKERS; i++) { enemies.push_back(new Tracker(generateRandomPostition(), 'T', getPlayer())); }

//    for (int i = 0; i < NUM_OF_LOUNGERS; i++) { enemies.push_back(std::make_unique<Lounger>(generateRandomPostition(), 'L')); }
//    for (int i = 0; i < NUM_OF_HYPERS; i++) { enemies.push_back(std::make_unique<Hyper>(generateRandomPostition(), 'H')); }
//    for (int i = 0; i < NUM_OF_AGGRESSORS; i++) { enemies.push_back(std::make_unique<Aggressor>(generateRandomPostition(), 'A', getPlayer())); }
}

/** call the move function for each respectiv type of all enemies */
void Game::allEnemiesMove() {
    bool moveSuccessful;
    for (size_t i = 0; i < (this->enemies.size()); i++) { enemies.at(i)->move(); }
}

/** Determine which enemy type are at this postion.
 * @parameter currentCellPos is the current cell position (x,y) beening checked.
 * @return a string of 3 characters representing a Scout 'S', Wanderer 'W', or Tracker 'T'.
 * if either some or all are missing a empty char ' ' holds it place. 
 * Note multiple of same type in the cell is represented by 1 char */
std::string Game::whichEnemyHere(const Position &currentCellPos) const {
    std::string typeInRoom;
    bool hasScout {false};
    bool hasWanderer {false};
    bool hasTracker {false};

    for (size_t i = 0; i < (this->enemies.size()); i++) {
        if ( (currentCellPos) == (this->enemies.at(i)->getPosition()) ) {
            if(this->enemies.at(i)->getType() == 'S') { hasScout = true; }
            else if(this->enemies.at(i)->getType() == 'W') { hasWanderer = true; }
            else if(this->enemies.at(i)->getType() == 'T') { hasTracker = true; }
            else {}
        }
    }
    if((hasScout == true) && (hasWanderer == true) && (hasTracker == true)) {return "SWT";}
    else if((hasScout == true) && (hasWanderer == true)) {return "SW ";}
    else if((hasScout == true) && (hasTracker == true)) {return "S T";}
    else if((hasWanderer == true) && (hasTracker == true)) {return " WT";}
    else if(hasScout == true) {return "S  ";}
    else if(hasWanderer == true) {return " W ";}
    else if(hasTracker == true) {return "  T";}
    
    return "   ";
}

/** check if player and loot are on the same position
 * @return true if player position == loot position, else false */
bool Game::isAbleToCarry() const {
    if ( (this->player->getPosition()) == (this->loot->getPosition()) ) { return true; }
    else { return false; }
}

/** generate a random postition within bounds of the grid and 1 cell away from player
 * @return a randomly generate postion object */
Position Game::generateRandomPostition() {
    size_t xCoord = randomRangeChrono(1, (NUM_OF_COLUMNS-1)); 
    size_t yCoord = randomRangeChrono(1, (NUM_OF_ROWS-1)); 
    Position pos(xCoord, yCoord);
    return pos;
}

/** Generates a random Number between a given range, using high-resolution clock for seeding
 * @parameter start is the start of the range from. 
 * @parameter end is the end of the range to. */    
int Game::randomRangeChrono(const int start, const int end) {
    auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    static std::default_random_engine rndEng(seed);
    std::uniform_int_distribution<int> uniformDist(start, end);
    return uniformDist(rndEng);
}