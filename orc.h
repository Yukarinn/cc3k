#ifndef ORC_H
#define ORC_H
#include "enemy.h"

class Goblin;
class Orc: public Enemy {
	public: 
		Orc();
		~Orc();
		bool strike(Goblin& other) override;
};
#endif
