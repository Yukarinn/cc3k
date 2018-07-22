#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"

class Treasure;

class Dragon: public Enemy {
	Treasure* hoard;
	public: 
		Dragon();
		~Dragon();
		void defeat() override;
		Treasure* getHoard() const;
		void setHoard(Treasure* hoard);
}
#endif
