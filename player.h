#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Treasure;
class Potion;

class Player: public Character {
    int maxHp;
    int baseAtk;
    int baseDef;
    int gold;
public:
    Player(std::string name, int hp, int atk, int def, int max_hp, int base_hp, int base_def);
    ~Player();
    void reset();
    int getMaxHp() const;
    int getBaseAtk() const;
    int getBaseDef() const;
    int getGold() const;
    int setGold();
    void die();
		void pick(Treasure& treasure);
		void drink(Potion& potion);

}
#endif
