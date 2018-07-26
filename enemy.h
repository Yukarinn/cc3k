#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
class Player;
class Enemy: public Character {
	public: 
		Enemy(std::string name, char display, int hp, int atk, int def);
		~Enemy();
		virtual void drop();
		virtual std::string act();
		std::string strike(Player* other);
	protected:
		Cell* findPlayer();
		void move();
};

#endif
