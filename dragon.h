#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"

class Treasure;
class Cell;

class Dragon: public Enemy {
    Treasure* hoard;
public: 
    Dragon();
    ~Dragon();
    std::string act() override;
    void drop() override;
    Treasure* getHoard() const;
    void setHoard(Treasure* hoard);
private:
    Cell* dragonFindPlayer();
};
#endif
