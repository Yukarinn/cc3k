#ifndef GOBLIN_H
#define GOBLIN_H
#include "player.h"

class Orc;
class Goblin: public Player {
	public: 
		Goblin();
		~Goblin();
		void beStruckBy(Orc& other) override;
}

#endif
