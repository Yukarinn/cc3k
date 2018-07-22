#include "game.h"
#include "player.h"
#include "cell.h"
#include "floor.h"

Game::Game()
{
    // make the clean floor
}

void Game::startGame()
{
    //player // new race
    floor = new Floor(cleanFloor, player);
}

void Game::endGame()
{
    
}

void Game::nextLevel()
{
    level++;
    delete floor;
    /*
    if (readFloor)
    {
        readfloors();
    }
     */
    floor = new Floor(cleanFloor, player);
}
void Game::toggleFreeze()
{
    // mob.dontact() 
}
void Game::usePotion(Direction dir)
{
    
}

void Game::playerAttack(Direction dir)
{
    
}

void Game::playerMove(Direction dir)
{
    Cell *moveto = findCell(dir);
    player->move(moveto);
    // check if stairs
    if (moveto->getTerrain() == Terrain::Stairs)
    {
        // set stairs->player object to nullptr
        moveto->setObject(nullptr);
        nextLevel();
    }
    
}
void Game::readFloorMode()
{
    readFloor = true;
}
void Game::readFloors(std::string fileName)
{
    
}

std::string Game::displayMenu()
{
    
}

std::string Game::displayAction()
{
    
}

Player * Game::getPlayer()
{
    
}
