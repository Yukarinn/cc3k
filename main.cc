#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "game.h"
#include "player.h"

using namespace std; 


int main(int argc, char *argv[]) {
	
	cin.exceptions(ios::eofbit|ios::failbit);
	srand(time(NULL));	 // use time for random seed

	bool custom = false; // flag to tell if we are using a custom map file
	string file;         // name of custom map file
	
	if (argc > 1) {
		if (argc > 2) {
			cerr << "Usage: "<< argv[0] << " FILE.TXT" << endl;
			return 1;
		}
		custom = true;	
		file = argv[1];
	}
	

	string buf; // use to read in user command
	
	Game * game;
	if (!custom)
		game = new Game();
	else
		game = new Game(file);
	
	game->selectPlayer(); // start the game
	game->startLevel();	
	game->draw();
		
	vector<string> directions = game->getDirections(); // list of cardinal directions

	try {
		while (true) { // main game loop
			try {
				cin >> buf;
				if (find(directions.begin(), directions.end(), buf) != directions.end()) {
					game->playerMove(buf); // player move command
				}	
				else if (buf == "u") {
					string dir;
					cin >> dir;
					game->usePotion(dir); // player use potion command
				} 
				else if (buf == "a") {
					string dir;
					cin >> dir;
					game->playerAttack(dir); // player attack command
				}
				else if (buf == "f") {
					game->toggleFreeze();   // freeze enemy command
				}
				else if (buf == "r") {  // restart command
					delete game;          // deletes, recreates, and restarts the game
					if (!custom)
						game = new Game();
					else
						game = new Game(file);
					game->selectPlayer(); 
					game->startLevel();	
					game->draw();
					continue;	
				}
				else if (buf == "q") { // quit command
					delete game;
					break;
				}
				else if (buf == "h") { // turn on hidden DLC!
					game->toggleHidden();
				}	
				else
					continue;
				// game can end when player reaches stairs or hp drops below 0
				if (game->isGameOver()) {  // reached stairs?
					game->showFinal();
					continue;
				}

				game->mobAct();  // make enemies act
				game->endTurn();
				
				if (game->isGameOver()) {  // zero hp?
					game->showFinal();				
					continue;
				}

				game->draw();

			} catch (exception& e) {

				if (cin.eof()) {
					delete game;
					break;
				}
				cout << e.what() << endl;
				game->draw();
			}
		}
	} catch (exception& e) {}
}
