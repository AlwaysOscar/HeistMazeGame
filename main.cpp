#include <iostream>
#include <cctype> // toupper
#include "game.h"
//#include <memory> // For std::maKe_unique

// Oscar Rodriguez
// Started 8/21/2023
// Edited 9/5/2023

void playGame();
void updateGameState(Game &game);
void printEndScreen(const Game &game);

int main(int argc, char const *argv[]) {
    playGame();
    return 0;
}

void playGame() {
    char playAgain;
    do {
        Game game;
        char inputMove;
        bool moveSuccessful;

        while( game.getPlayerStatus() == 'P' ) {
            moveSuccessful = false;
            std::cout << game;
            std::cout << std::endl << "Your move [N,S,W,E,P,C]:  ";
            std::cin >> inputMove;
            while (!moveSuccessful) {
                inputMove = std::toupper(inputMove);
                try {
                    game.move(inputMove);
                    moveSuccessful = true;
                }
                catch(const InvalidMoveException& e) { 
                    std::cerr << "Error: " << e.what();
                    std::cin >> inputMove; 
                }
            }
            game.allEnemiesMove();
            if (game.getIsCarryingLoot() == true) { game.getLoot()->move(inputMove); }
            updateGameState(game);
            std::cout << "\x1B[2J\x1B[H"; // Clear screen and move cursor to top-left
        }
        printEndScreen(game);
        std::cout << "would you like to play again? (Y/N) ";
        std::cin >> playAgain;
        playAgain = std::toupper(playAgain);
    } while (playAgain == 'Y');

    std::cout << "\x1B[2J\x1B[H"; // Clear screen and move cursor to top-left
    std::cout << "Goodbye";
}

void updateGameState(Game &game) {
    /* Lose condition, Player is on same tile as Enemy */
    for (size_t i = 0; i < (game.getEnemies().size()); i++) {
        if ( (game.getPlayer()->getPosition()) == (game.getEnemies().at(i)->getPosition()) ) {
            game.setPlayerStatus('L');
            game.setCauseOfLost(game.getEnemies().at(i)->getType());
            return;
        }
    }
    /* Win condition, Player is on tile  (0,0) with Loot */
    if ( (game.getPlayer()->getPosition() == Position(0,0)) 
            && (game.getLoot()->getPosition() == Position(0,0)) ) {
        game.setPlayerStatus('W');
        return;
    }
    
    /* Continue Playing Condition neither of the above is meant */
    else { return; }
}

void printEndScreen(const Game &game) {
    std::cout << game;
    std::cout << std::endl << "-----------------------------------" << std::endl;
    std::cout << "\tGame Over" << std::endl;

    if(game.getPlayerStatus() == 'W') {
        std::cout << "\tYou Win!" << std::endl;
        std::cout << "Must've been luck I guess... ¯\\_(ツ)_/¯" << std::endl;
    }
    else {
        std::cout << "\tYou lose!" << std::endl;
        std::cout << "Death by Enemy Type: " << game.getCauseOfLost() << std::endl;
    }
    std::cout << "-----------------------------------" << std::endl;
}

/*  Friend function implementation
    Output Game layout and positions of persons */
std::ostream &operator<<(std::ostream &os, const Game &game) {
    Position currentGridPos;
    Position currentGridPos2;
    
    os << "Heist mission in progress" << std::endl;
    for (size_t y = 0; y < NUM_OF_ROWS; y++) {
        size_t x = 0;                                       // actual x-coordinate componet (i from loop isn't valid)
        size_t x2 = 0;                                      // actual x-coordinate componet (i from loop isn't valid)
        for (size_t i = 0; i <= (NUM_OF_COLUMNS * 3); i++) {
            currentGridPos = Position(x, y);
            currentGridPos2 = Position(x2, y);
            
            /* prints top border to fit appropriate #of columns */
            if ( ((i >= 0) && (i < NUM_OF_COLUMNS)) ) {
                if(i == 0) {                                // reset x position bc we are going down a row
                    x = 0;
                    x2 = 0;
                }
                os << "----";
            }

            /* prints top portion of individual cell block of the enemy type there */
            else if ((i >= NUM_OF_COLUMNS) && (i < NUM_OF_COLUMNS * 2)) {
                if (i == NUM_OF_COLUMNS) { os << std::endl; }   // top border max length reached print newline
                os << '|' << (game.whichEnemyHere(currentGridPos));
                ++x;
            }

            /* prints bottom portion of individual cell block of the ally type there */
            else if ((i >= NUM_OF_COLUMNS * 2) && (i <= NUM_OF_COLUMNS * 3)) {
                if (i == NUM_OF_COLUMNS * 2) // end of top portion column print '|' right column border and newline
                { os << '|' << std::endl; }

                if (i == NUM_OF_COLUMNS * 3) // end of bottom portion column print '|' right column border and newline
                { os << '|' << std::endl; }

                else if ((game.player->getPosition()) == (game.loot->getPosition()) 
                    && (currentGridPos2 == (game.player->getPosition()))) {
                    os << '|' << 'P' << ' ' << 'L';
                    ++x2;
                }

                else if (currentGridPos2 == (game.player->getPosition())) {
                    os << '|' << ' ' << 'P' << ' ';
                    ++x2;
                }

                else if (currentGridPos2 == (game.loot->getPosition())) {
                    os << '|' << ' ' << 'L' << ' ';
                    ++x2;
                }

                else {
                    os << "|   ";
                    ++x2;
                }
            }
        }
    }
    /* prints bottom border to fit appropriate #of columns */
    for (size_t i = 0; i < NUM_OF_COLUMNS; i++) { os << "----"; }
    return os;
}