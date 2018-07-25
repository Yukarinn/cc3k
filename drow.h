#ifndef DROW_H
#define DROW_H
#include "player.h"

class Potion;
class Drow: public Player {
public: 
    Drow();
    ~Drow();
    void drink(Potion* potion) override;
};
#endif
