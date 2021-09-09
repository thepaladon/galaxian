#include "enemy.h"
#include "bullet.h"
#include "surface.h"
#include "template.h"
#include "game.h"

#include <stdio.h>

	using namespace Tmpl8;

	static Sprite deathState(new Surface("assets/explosion2.png"), 5);

	Enemy::Enemy() {
		stateOfEnemy = 1;
		directionGoingLeft = true;
		frame = 0;
		timer = 1000;
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
		case 3: DeathAnimation();
			break;
		case 4: 
			break;
		}
		
	}
	
	void Enemy::DeathAnimation() {
		deathState.SetFrame(frame);
		deathState.Draw(screen, x, y);
		

		if (enemyTime > timer) {
			frame++;
			timer += 500;
		}

		if (frame >= 4) {
			stateOfEnemy = 4;
		}
	}
	
	void Enemy::EnemyCollision(Bullet* bullet) {

		if (bullet->getX()< x + 10 &&
			bullet->getX() > x &&
			bullet->getY() - 2 < y + 7 &&
			bullet->getY() + 2 > y)
		{
			timer = enemyTime + timer;
			enemyDead = true;
			stateOfEnemy = 3;
			bullet->ResetAfterHit(1);
		}
	}

	void Enemy::SetCoords(int Ex, int Wy) { x = Ex; y = Wy; }
	void Enemy::SetEnemyTime(float time) { enemyTime = time; }

	bool Enemy::GetAliveState() { return enemyDead; }

	int Enemy::GetX() { return x; }
	int Enemy::GetY() { return y; }

