#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <string>

class Cell;
class Player;

class Floor {
    std::vector<std::vector<Cell*>> theFloor;
    Player * player;
    std::vector<std::vector<int>> layout;
    std::vector<vector<Cell *>> chambers;
    std::vector<Enemy *> mobs;
public:
    Floor(std::vector<std::vector<char>> plan); // spawn everything
    ~Floor();
    std::string draw();
    void setPlayer(Player* player);
    Player* getPlayer();
    void mobAct();
    
    void spawnPlayer();
    void spawnStairs();
    void spawnPotions();
    void spawnGold();
    void spawnEnemies();
    
    void setup();
private:
    void floodfill(int i, int j, int chamber);
};

#endif
