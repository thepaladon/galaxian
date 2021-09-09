#pragma once  //file should ever only be inlcuded once
#include "surface.h"

namespace Tmpl8 {

	class Bullet
	{
	public:
		Bullet();
		~Bullet(); //to clean up when a class dies
		void BulletMechanics(int playerX, int playerY);
		void BulletFired();
		void BulletDraw(Tmpl8::Surface* screen);
		void BulletFollowPlayer(int playerX, int playerY);
		void SetBulletState(int i);
		void ResetAfterHit(int i);

		bool SetFireReady(bool readyAgain);
		int getX();
		int getY();

	private:
		int x, y;
		int bulletState = 1; // 1 - follows player; 2 - is firing; 3 - is reseting;
		bool fireReady = true;

	};
};

