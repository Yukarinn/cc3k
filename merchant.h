#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"
class Merchant: public Enemy {
	static aggro = false;
	public: 
		Merchant();
		~Merchant();
		void defeat() override;
}
#endif
