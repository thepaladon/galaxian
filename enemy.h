#include "bullet.h"
#include "surface.h"

namespace Tmpl8 {
	class Enemy
	{
	public:
		Enemy();
		~Enemy();
		void SetTarget(Surface* surface) { screen = surface; }
		void IdleAnimation(bool directionGoingRight, int max);
		void DeathAnimation();
		void EnemyMechanics(bool directionGoing, int max);
		void EnemyCollision(Bullet* bullet);
		void SetCoords(int Ex, int Wy);
		void SetEnemyTime(float time);

		bool SetDeath(bool death); 
		bool GetAliveState();
		int GetX();
		int GetY();

	private:
		int x, y;
		int stateOfEnemy; // 1 - idle in group, 2 - attacking, 3 - dying
		int directionGoingLeft = true;
		int frame;
		int timer;
		float enemyTime;
		bool enemyDead = false;
		Surface* screen;
	};

};