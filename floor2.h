#ifndef FLOOR_H
#define FLOOR_H
#include "human.h"
#include "dragon.h"
#include "merchant.h"
#include "orc.h"
#include "halfling.h"
#include "dwarf.h"
#include "elf.h"
#include <memory>
#include <vector>
#include <string>

class Cell;
class Player;
class Enemy;

class Floor {
    std::vector<std::vector<Cell*>> theFloor;
    Player * player;
		Cell * customPlayerCell = nullptr;
    std::vector<std::vector<int>> layout;
    std::vector<std::vector<Cell *>> chambers;
    std::vector<Enemy*> mobs;    
		bool custom = false;    
public:
    Floor(std::vector<std::vector<char>> plan);
    ~Floor();
    std::string draw();
    void setPlayer(Player* player);
    Player* getPlayer();
    void setup();
    void spawn(); // spawn everything
		std::string mobAct();
private:
    void floodfill(int i, int j, int chamber);
		void spawnPlayer(int chamberNum);
    void spawnStairs(int chamberNum);
    void spawnPotions();
    void spawnGold();
    void spawnEnemies();

};

#endif
