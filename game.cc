#include "game.h"
#include "floor.h"
#include "cell.h"
#include "player.h"

#include "shade.h"
#include "vampire.h"
#include "drow.h"
#include "goblin.h"
#include "troll.h"
#include "potion.h"
#include "treasure.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

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
    for (auto each: floors) {
        delete each;
    }
		delete player;
}

void Game::selectPlayer() {

	cout << "Please select your race:" <<endl;
	for (int i = 0; i < getRaces().size(); i ++) {
		cout << getRaces()[i][0] << ": " << getRaces()[i] << endl;
	}
	char selection;
	cin >> selection;
	while (selection != 's' && selection != 'd' && selection != 'v' && selection != 'g' && selection != 't') {
		cout << "Please select a valid race." << endl;
		cin >> selection;
	}
	newPlayer(selection);
}

void Game::newPlayer(char race) {
    switch(race) {
        case 's':
            player = new Shade();
            return;
        case 'd':
            player = new Drow();
            return;
        case 'v':
            player = new Vampire();
            return;
        case 't':
            player = new Troll();
            return;
        case 'g':
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
    cout << floors[level - 1]->draw() << endl;
		cout << displayMenu() << endl;
}

void Game::startLevel() {
    //cout << "one" << endl;
    floors[level - 1]->setPlayer(player);
    //cout << "two" << endl;
    floors[level - 1]->setup();
    //cout << "three" << endl;
    if (!readFloor)
    {
        floors[level - 1]->spawn();
    }
}

void Game::nextLevel()
{
		if (level == 5) {
			gameOver = true;
			return;
		}
    level ++;
    floors[level - 1]->setPlayer(player);
    floors[level - 1]->setup();
    if (!readFloor)
    {
        floors[level - 1]->spawn();
    }
		player->reset();
    draw();
}

Cell* Game::findCell(std::string dir)
{
		Cell* cell = player->getCell();
    int r = cell->getPos().first;
    int c = cell->getPos().second;
		int nr = r;
		int nc = c;

    if (dir == "no")
			nr --;
    else if (dir == "so")
			nr ++;
    else if	(dir == "ea")
			nc ++;
    else if (dir == "we")
			nc --;
    else if (dir == "ne") {
			nr --;
			nc ++;
		}
    else if (dir == "nw") {
			nr --;
			nc --;
		}
    else if (dir == "se") {
			nr ++;
			nc ++;
		}
    else if (dir == "sw") {
			nr ++;
			nc --;
		} else {
			return nullptr;
		}
		vector<Cell*> neighbours = cell->getNeighbours();
		for (auto each: neighbours) {
			if (each->getPos() == make_pair(nr, nc))
				return each;
		}
		return nullptr;
}


void Game::usePotion(std::string dir)
{
    Cell *location = findCell(dir);
    if (location && location->getObject()) {
        if (location->getObject()->getType() == ObjectType::Potion) {
						Potion* potion = dynamic_cast<Potion*>(location->getObject()); 	
						Potion::see(potion->getPotionType());
						action = "Player drinks the " + potion->getEffect() + ". ";
						player->drink(potion);
						return;
				}
		}
		action = "Invalid action. ";
		throw InvalidAction();
}


void Game::playerAttack(std::string dir)
{
    Cell *location = findCell(dir);
    if (location && location->getObject()) {
        if (location->getObject()->getType() == ObjectType::Enemy) {
						Enemy* enemy = dynamic_cast<Enemy*>(location->getObject());
            action = player->strike(enemy);
						return;
				}
		}
		action = "Invalid action. ";
		throw InvalidAction();
}

string Game::getFullDirection(string dir) {
	if (dir == "no")
		return "north";
	if (dir == "so")
		return "south";
	if (dir == "ea")
		return "east";
	if (dir == "we") 
		return "west";
	if (dir == "se") 
		return "south east";
	if (dir == "sw")
		return "south west";
	if (dir == "ne")
		return "north east";
	if (dir == "nw")
		return "north west";
}

void Game::playerMove(std::string dir)
{	
		string gold = "";
    Cell *newCell = findCell(dir);
		if (newCell && newCell->canMoveTo()) {
			gold = player->move(newCell);
		}	else {
			action = "Invalid action. ";
			throw InvalidAction();
		}
    // check if stairs
    if (newCell->getTerrain() == Terrain::Stairs)
    {
        // set stairs->player object to nullptr
        newCell->setObject(nullptr);
        nextLevel();
				action = "Player goes up the stairs to the next level.";
				return;
		}
		action = "Player moves " + getFullDirection(dir);
		string potion = player->spot();
		if (gold != "" && potion != "") {
			action += ", " + gold + +", and spots " + potion;
		}	else if (gold != "") {
			action += " and " + gold + ". ";
		} else if (potion != "") {
			action += " and spots " + potion + ". ";
		} else {
			action += ". ";
		}
}

void Game::mobAct() {
	if (!isFrozen)
		action += floors[level - 1]->mobAct();
}

void Game::endTurn() {
	if (player->getHp() == 0) {
		gameOver = true;
		action += "PC has died! ";
		return;
	}
	if (player->getName() == "Troll") {
		if (player->getMaxHp() != player->getHp()) {
			player->setHp(min(player->getMaxHp(), player->getHp() + 5));
			action += "PC heals 5 HP passively. ";
		}
	}
}


void Game::toggleFreeze()
{
    isFrozen = !isFrozen;
		if (isFrozen)
			action = "Freeze! ";
		else
			action = "Unfreeze! ";
}

void Game::readFloorMode()
{
    readFloor = true;
}

std::string Game::displayMenu()
{
    stringstream menu;
    menu  << "Race: "  << player->getName() << "\tGold " << player->getGold();
  
		menu << "\t\t\t\t\t\t";
		
    menu << "Floor: " << level << "\n";
    menu << "HP: " << player->getHp() << "\n";
    menu << "Atk: " << player->getAtk() << "\n";
    menu << "Def: " << player->getDef() << "\n";
    menu << "Action: " << action << "\n";
		action = "";
    return menu.str();
}

Player* Game::getPlayer() const
{
    return player;
}

bool Game::isGameOver() {
	return gameOver;
}
