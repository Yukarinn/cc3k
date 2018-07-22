#include "game.h"
#include "player.h"

Game::Game()
{
    // make the clean floor
}

void Game::startGame()
{
    player = new Player();
    floor0 = new Floor(cleanFloor, player);
}

void Game::endGame(bool isEnd);
void Game::nextlevel()
{
    level++;
    delete floor;
    floor = new Floor(cleanFloor, player);
}
void Game::toggleFreeze();
void Game::usePotion(Direction dir);
void Game::playerAttack(Direction dir);
void Game::playerMove(Direction dir)
{
    //move the player
    // check if stairs
    if ()
    {
        // set stairs->player object to nullptr
    }
    nextlevel(player)
}
void Game::readFloorMode()
{
    readFloor = true;
}
void Game::readFloors(std::string fileName)
{
    
}
std::string Game::displayMenu();
std::string Game::displayAction();
Player * Game::getPlayer();
