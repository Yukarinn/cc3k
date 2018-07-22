#ifndef GAME_H
#define GAME_H

#include <string>

class Floor;
class Player;
class Cell;

enum Direction {
    N, NE, E, SE, S, SW, W, NW
};
class Game {
    Floor *floor;
    Cell * cleanFloor[30][79];
    int level;
    Player * player;
    int plyr, plyc; // tracks where the player is 
    bool readFloor = false;
    
public:
    Game();
    void startGame();
    void endGame(); // display the scoreboard
    void nextLevel();
    void toggleFreeze();
    Cell *findCell(Direction dir);
    void usePotion(Direction dir);
    void playerAttack(Direction dir);
    void playerMove(Direction dir);
    void readFloors(std::string fileName);
    void readFloorMode();

    std::string displayMenu();
    std::string displayAction();
    Player * getPlayer() const;
};

#endif /* game_h */
