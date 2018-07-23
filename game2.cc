#include "game2.h"
#include "floor2.h"

#include "shade.h"
#include "vampire.h"
#include "drow.h"
#include "goblin.h"
#include "troll.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Game::Game(string file) {
	ifstream F{file};
	string line;
	for (int f = 0; f < 5; f ++) {
		vector<vector<char>> plan;
		for (int i = 0; i < 25; i ++) {
			vector<char> row;
			getline(F, line);
			for (int j = 0; j < 79; j ++) {
				row.push_back(line[j]);
			}
			plan.push_back(row);
		}
		floors.push_back(new Floor(plan));
	}
	level = 1;
}


Game::~Game() {
	delete player;
	for (auto each: floors) {
		delete each;
	}
}


void Game::newPlayer(int race) {
	switch(race) {
		case 1:
			player = new Shade();					
			return;
		case 2:
			player = new Drow();
			return;
		case 3:
			player = new Vampire();
			return;
		case 4:
			player = new Troll();
			return;
		case 5:
			player = new Goblin();
			return;
	}
}

vector<string> Game::getDirections() const {
	return directions;
}

vector<string> Game::getRaces() const {
	return races;
}

void Game::draw() {
	cout << "Level: " << level << endl;
	cout << floors.size() << endl;
	cout << floors[level - 1]->draw() << endl;
	cout << "*********************************************************" << endl;
}

void Game::startLevel() {
	floors[level - 1]->setPlayer(player);
	floors[level - 1]->setup();
	floors[level - 1]->spawn();
	draw();
}

void Game::playerMove(string direction) {

}
