#ifndef FLOOR_H
#define FLOOR_H

#include <vector>

class Cell;
class Player;
class Enemy;
class Object;

class Floor {
    Player * player;
    bool isFrozen;
    Object * theFloor[30][79];
    vector<vector<Cell *>> chambers; // vector of vector of chambers
    vector<Enemy *> mobs; //
    
    void spawnPlayer();
    void spawnStairs();
    void spawnPotions();
    void spawnGold();
    void spawnEnemies();
    
Public:
    Floor(); // spawn everything, shared pointer?
    ~Floor();
    void draw(); // display
    void clear();  // clear floor
    void mobAct();
}

#endif
