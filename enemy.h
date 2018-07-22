#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"

class Enemy: public Character {
	public: 
		Enemy(std::string name, int hp, int atk, int def);
		~Enemy();
		virtual void defeat() = 0;
		virtual void act();
}

#endif
