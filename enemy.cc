#include "enemy.h"

using namespace std;

Enemy::Enemy(string name, int hp, int atk, int def) Character(name, hp, atk, def) {}

Enemy::~Enemy() {}

void Enemy::act() {
	if (findPlayer() != nullptr) {
		Player* player = findPlayer();
		player.beStruckBy(this);
		return;
	}
}

