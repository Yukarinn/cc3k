#ifndef game_h
#define game_h

class Direction;
class Floor;
class Plyaer;

class Game {
    Floor *floor;
    Cell * cleanFloor[30][79];
    int level;
    Player * player;
    bool readFloor = false;
Public:
    Game();
    void startGame(Player * playerType);
    void endGame(); // display the scoreboard
    void nextLevel();
    void toggleFreeze();
    void usePotion(Direction dir);
    void playerAttack(Direction dir);
    void playerMove(Direction dir);
    void readFloors(std::string fileName);
    void readFloorMode();
    std::string displayMenu();
    std::string displayAction();
    Player * getPlayer() const;
}

#endif /* game_h */
