#ifndef FLOOR_H
#define FLOOR_H

#include <vector>

class Cell;
class Player;
class Enemy;
class Object;

class Floor {
    bool isFrozen;
    Cell * theFloor[30][79];
    vector<vector<Cell *>> chambers; // vector of vector of chambers
    vector<Enemy *> mobs; //
    
    void spawnPlayer();
    void spawnStairs();
    void spawnPotions();
    void spawnGold();
    void spawnEnemies();
    
Public:
    Floor(Cell *cleanFloor[30][79]); // spawn everything, shared pointer?
    ~Floor();
    void draw(); // display
    void mobAct();
}

#endif
