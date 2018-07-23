#include "game2.h"
#include "floor2.h"
#include "cell.h"
#include "player.h"

#include "shade.h"
#include "vampire.h"
#include "drow.h"
#include "goblin.h"
#include "troll.h"

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
    //cout << "one" << endl;
    floors[level - 1]->setPlayer(player);
    //cout << "two" << endl;
    floors[level - 1]->setup();
    //cout << "three" << endl;
    if (!readFloor)
    {
        floors[level - 1]->spawn();
    }
    draw();
}

void Game::nextLevel()
{
    level ++;
    floors[level - 1]->setPlayer(player);
    floors[level - 1]->setup();
    if (!readFloor)
    {
        floors[level - 1]->spawn();
    }
    draw();
}

void Game::endGame() // display the scoreboard
{
    
}

Cell Game::*findCell(std::string dir)
{
    int plyr = player->getCell()->getPos().first;
    int plyc = player->getCell()->getPos().second;
    int tempr, tempc;
    if (dir == "no")
    {
        tempr = plyr + 1;
        tempc = plyc;
    }
    else if (dir == "so")
    {
        tempr = plyr - 1;
        tempc = plyc;
    }
    else if (dir == "ea")
    {
        tempr = plyr;
        tempc = plyc + 1;
    }
    else if (dir == "we")
    {
        tempr = plyr;
        tempc = plyc - 1;
    }
    else if (dir == "ne")
    {
        tempr = plyr + 1;
        tempc = plyc + 1;
    }
    else if (dir == "nw")
    {
        tempr = plyr + 1;
        tempc = plyc - 1;
    }
    else if (dir == "se")
    {
        tempr = plyr - 1;
        tempc = plyc + 1;
    }
    else if (dir == "sw")
    {
        tempr = plyr - 1;
        tempc = plyc - 1;
    }
    
    if (! (floors[level - 1]->getCell[tempr][tempc]->getTerrain() == Terrain::WallV)
        (floors[level - 1]->getCell[tempr][tempc]->getTerrain() == Terrain::WallH)
        (floors[level - 1]->getCell[tempr][tempc]->getTerrain() == Terrain::Empty))
    {
        return floors[level - 1]->getCell[tempr][tempc];
    }
    else // cant step on / not valid floors[level - 1]->getCell
    {
        return floors[level - 1]->getCell[plyr][plyc];
    }
}

void Game::usePotion(std::string dir)
{
    Cell *location = findCell(dir);
    if (location->getObject())
    {
        if (location->getObject()->getType() == ObjectType::Potion)
        {
            player->drink(location->getObject());
        }
    }
    // else - not a potion so do nothing
}
void Game::playerAttack(std::string dir)
{
    Cell *location = findCell(dir);
    if (location->getObject())
    {
        if (location->getObject()->getType() == ObjectType::Enemy)
        {
            location->getObject()->beStruckBy(player);
        }
    }
}

void Game::playerMove(std::string dir)
{
    Cell *moveto = findCell(dir);
    player->move(moveto);
    plyr = moveto->getPos().first;
    plyc = moveto->getPos().second;
    // check if stairs
    if (moveto->getTerrain() == Terrain::Stairs)
    {
        // set stairs->player object to nullptr
        moveto->setObject(nullptr);
        nextLevel();
    }
    if (!isFrozen)
    {
        floors[level - 1]->mobAct();
    }
}

void Game::toggleFreeze()
{
    isFrozen = !isFrozen;
}

void Game::readFloorMode()
{
    readFloor = true;
}

std::string Game::displayMenu()
{
    stringstream menu;
    menu  << "Race: "  << player->getName() << " Gold " << player->getGold();
    for (int i=0; i<50; i++)
    {
        menu << " ";
    }
    menu << "Floor: " << level << "\n";
    menu << "HP: " << player->getHp() << "\n";
    menu << "Atk: " << player->getAtk() << "\n";
    menu << "Def: " << player->getDef() << "\n";
    menu << "Action: " << action << "\n";
    return menu.str();
}

Player Game::*getPlayer() const
{
    return player;
}


