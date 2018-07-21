#ifndef game_h
#define game_h

class Direction;
class Floor;

class Game {
    Floor * floor;
    int level;
Public:
    void startGame();
    void endGame(bool isEnd);
    void startLevel();
    void endLevel();
    void toggleFreeze();
    void usePotion(Direction dir);
    void playerAttack(Direction dir);
    void playerMove(Direction dir);
    std::string displayMenu();
    std::string displayAction();
    void getPlayer(std::string race);
}

#endif /* game_hpp */
