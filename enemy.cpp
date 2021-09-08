#include "enemy.h"
#include "bullet.h"
#include <stdio.h>
using namespace Tmpl8;

	Enemy::Enemy() {
		
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

	
	void Enemy::EnemyCollision(Bullet* bullet) {

		if (bullet->getX()< x + 10 &&
			bullet->getX() > x &&
			bullet->getY() - 2 < y + 7 &&
			bullet->getY() + 2 > y)
		{
			enemyDead = true;
			bullet->ResetAfterHit(1);
		}
	}

	void Enemy::SetCoords(int Ex, int Wy) { x = Ex; y = Wy; }
	
	bool Enemy::GetAliveState() { return enemyDead; }

	int Enemy::GetX() { return x; }
	int Enemy::GetY() { return y; }


