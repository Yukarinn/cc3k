#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player: public Character {
	int maxHp;
	int baseAtk;
	int baseDef;
	int gold;
	public: 
		Player(std::string name, int hp, int atk, int def, int max_hp, int base_atk, int base_def);
		~Player();
		virtual void reset() = 0;
		int getMaxHp() const;
		int getBaseAtk() const;
		int getBaseDef() const;
		int getGold() const;
		void setGold(int gold);
		void die();
}
#endif
