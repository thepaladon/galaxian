#include "bullet.h"

namespace Tmpl8 {
	class Enemy
	{
	public:
		Enemy();
		~Enemy();
		void IdleAnimation(bool directionGoingRight, int max);
		void EnemyMechanics(bool directionGoing, int max);
		void EnemyCollision(Bullet* bullet);
		void SetCoords(int Ex, int Wy);

		bool SetDeath(bool death); 
		bool GetAliveState();
		int GetX();
		int GetY();


	private:
		int x, y;
		int stateOfEnemy; // 1 - idle in group, 2 - attacking
		int directionGoingLeft = true;
		bool enemyDead = false;

	};

};