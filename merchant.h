#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"
#include <string>

class Merchant: public Enemy {
	static bool aggro;
	public: 
		Merchant();
		~Merchant();
		std::string act() override;
    static void setAggro(bool aggro);
    void drop() override;
};
#endif
