#include "enemy.h"
using namespace Tmpl8;

	Enemy::Enemy() {
		x = 100;
		y = 20;
		stateOfEnemy = 1;
		directionGoingLeft = true;
	
	}
	Enemy::~Enemy() {};

	void Enemy::IdleAnimation(bool directionGoingRight, int max) {
		if (directionGoingRight)
			x++;
		else if (!directionGoingRight)
			x--;
	}

	void Enemy::EnemyMechanics(bool directionGoing, int max) {
		switch (stateOfEnemy) {
		case 1: IdleAnimation(directionGoing, max);
			break;
		case 2:
			break;
		}

	}

	void Enemy::SetCoords(int Ex, int Wy) { x = Ex; Wy = y; }

	bool Enemy::SetDeath(bool death) 
	{ 
	enemyDead = death; 
	return death;
	}
	
	bool Enemy::GetAliveState() { return enemyDead; }

	int Enemy::GetX() { return x; }
	int Enemy::GetY() { return y; }


