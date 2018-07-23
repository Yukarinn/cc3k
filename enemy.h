#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"

class Enemy: public Character {
	public: 
		Enemy(std::string name, char display, int hp, int atk, int def);
		~Enemy();
		virtual void drop();
		virtual void act();
	private:
		Cell* findPlayer();
};

#endif
