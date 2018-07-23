#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include <exception>
class Floor;
class Player;
class Cell;

class InvalidAction: public std::exception {
	virtual const char* what() const throw() {
		return "Invalid Action";
	}
};

class Game {
    std::vector<Floor*> floors;
		Player* player;
    std::string action = "Player character has spawned." ;
    int level;
    
    std::vector<std::string> directions = {"no", "so", "ea", "we", "ne", "nw", "se", "sw"};
    std::vector<std::string> races = {"shade", "drow", "vampire", "troll", "goblin"};
    
    int plyr, plyc; // tracks where the player is
    bool readFloor = false;
    bool isFrozen = false;
		bool gameOver = false;
    
public:
    Game(std::string file = "default2.txt");
    ~Game();
    void newPlayer(int player);
    std::vector<std::string> getDirections() const;
    std::vector<std::string> getRaces() const;
    void startLevel();
    void draw();
    void nextLevel();
    void endGame(); // display the scoreboard
    
    Cell *findCell(std::string direction);
    void usePotion(std::string direction);
    void playerAttack(std::string direction);
    void playerMove(std::string direction);
		void mobAct();    
    void endTurn();
		void toggleFreeze();
    void readFloorMode();
		bool isGameOver();    
    std::string displayMenu();
    std::string displayAction();
    Player *getPlayer() const;
private:
		std::string getFullDirection(std::string dir); 
};

#endif
