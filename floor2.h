#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <string>

class Cell;
class Player;
class Enemy;

class Floor {
    std::vector<std::vector<Cell*>> theFloor;
    Player * player;
    std::vector<std::vector<int>> layout;
    std::vector<std::vector<Cell *>> chambers;
    std::vector<Enemy *> mobs; 
    
    void spawnPlayer(Player * thePlayer, int chamberNum);
    void spawnStairs(int chamberNum);
    void spawnPotions();
    void spawnGold();
    void spawnEnemies();
    
    void mobAct();
    
public:
    Floor(std::vector<std::vector<char>> plan);
    ~Floor();
    std::string draw();
    void setPlayer(Player* player);
    Player* getPlayer();
    void setup();
    void spawn(); // spawn everything
private:
    void floodfill(int i, int j, int chamber);
};

#endif
