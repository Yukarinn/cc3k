#ifndef HALFLING_H
#define HALFLING_H
#include "enemy.h"

class Halfling: public Enemy {
	public: 
		Halfling();
		~Halfing();
		void beStruckBy(Character& other) override;
}
#endif
