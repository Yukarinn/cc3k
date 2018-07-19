#ifndef ORC_H
#define ORC_H
#include "enemy.h"

class Goblin;
class Orc: public Enemy {
	public: 
		Orc();
		~Orc();
		void strike(Goblin& other) override;
}
#endif
