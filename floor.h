#ifndef FLOOR_H
#define FLOOR_H
#include <memory>
#include <vector>
#include <string>

class Cell;
class Player;
class Enemy;

class Floor {
    std::vector<std::vector<Cell*>> theFloor; 
    Player * player;
		Cell * customPlayerCell = nullptr; // only non nullptr if custom map, in which case we keep track of starting location of player
    std::vector<std::vector<int>> layout; // layout[i][j] gives the chamber number of theFloor[i][j], or 0 if not a chamber
		std::vector<std::vector<bool>> seen; // a player can always see tiles which he has seen before (bonus dlc)
    std::vector<std::vector<Cell *>> chambers; // keeps list of cells for each chamber
    std::vector<Enemy*> mobs;  // list of enemies in this chamber
		bool custom = false;  // is custom map? (non default map)
public:
    Floor(std::vector<std::vector<char>> plan);
    ~Floor();
    std::string draw();  // draws the entire map, (bonus dlc based on what player can see)
    void setPlayer(Player* player);
    Player* getPlayer();
    void setup();
    void spawn(); // spawn everything
		std::string mobAct();
private:
		bool nextToChamber(Cell* other, int chamber);
		bool canSee(Cell* other);
    void floodfill(int i, int j, int chamber);
		void spawnPlayer(int chamberNum);
    void spawnStairs(int chamberNum);
    void spawnPotions();
    void spawnGold();
    void spawnEnemies();

};

#endif
