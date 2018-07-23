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
    
    bool isFrozen = false;
		bool gameOver = false;
    
public:
    Game(std::string file="empty.txt");
    ~Game();
		void selectPlayer();
    std::vector<std::string> getDirections() const;
    std::vector<std::string> getRaces() const;
    void startLevel();
    void draw();
    void nextLevel();
    void endGame(); // display the scoreboard 
    void endTurn();
		void toggleFreeze();
		bool isGameOver();    
    Player *getPlayer() const;
		void showFinal();
		void usePotion(std::string direction);
    void playerAttack(std::string direction);
    void playerMove(std::string direction);
		void mobAct();  
private:
		std::string getFullDirection(std::string dir); 	
    void newPlayer(char player);
		Cell *findCell(std::string direction);
		std::string displayMenu();
};

#endif
