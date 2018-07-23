#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"
class Merchant: public Enemy {
	static bool aggro;
	public: 
		Merchant();
		~Merchant();
    static void setAggro(bool aggro);
    void drop() override;
    void beStruckBy(Character &other) override;
};
#endif
