#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"
class Dragon: public Enemy {
	public: 
		Dragon();
		~Dragon();
		void defeat() override;
}
#endif
