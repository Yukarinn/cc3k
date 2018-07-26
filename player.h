#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include "character.h"

class Potion;
class Treasure;
class Cell;
class Enemy;

class Player: public Character {
protected:
    Treasure* onHoard = nullptr; // player can walk on top of a dragon hoard if the dragon is still alive, so this is temp location for hoad
    int maxHp;
    int baseAtk;
    int baseDef;
    int gold = 0;
public:
    Player(std::string name, int hp, int atk, int def, int max_hp, int base_hp, int base_def);
    ~Player();
    void reset();
    int getMaxHp() const;
    int getBaseAtk() const;
    int getBaseDef() const;
    int getGold() const;
    void setGold(int gold);
    void die();
    std::string move(Cell* cell);
    bool pick(Treasure* treasure);
    virtual void drink(Potion* potion);
    std::string spot();
    std::string strike(Enemy* enemy);
    std::string grab(Cell* cell);
};

#endif
