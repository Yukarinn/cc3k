#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player: public Character {
    int maxHp;
    int baseAtk;
    int baseDef;
    int gold;
public:
    Player(std::string name, int hp, int atk, int def, int max_hp, int base_hp, int base_def);
    ~Player();
    virtual void reset() = 0;
    int getMaxHp() const;
    int getBaseAtk() const;
    int getBaseDef() const;
    void setHp(int n);
    void setAtk(int n);
    void setDef(int n);
    int getGold() const;
    int setGold();
    void die();
}
#endif
