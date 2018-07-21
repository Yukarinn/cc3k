#include "floor.h"

void Floor::spawnPlayer();
void Floor::spawnStairs();
void Floor::spawnPotions();
void Floor::spawnGold();
void Floor::spawnEnemies();

Floor::Floor() {
    spawnPlayer();
    spawnStairs();
    spawnPotions();
    spawnGold();
    spawnEnemies();
}

void Floor::draw(); // display
void Floor::clear();  // clear floor
void Floor::mobAct();

