#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"
class Merchant: public Enemy {
	static bool aggro;
	public: 
		Merchant();
		~Merchant();
    static void setAggro();
    void defeat(); // override; - cant override if theres not virtual
    void beStruckBy(Character &other) override;
};
#endif
