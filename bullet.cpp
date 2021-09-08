#include "bullet.h"
#include "surface.h"
#include <stdio.h>

using namespace Tmpl8;

	Bullet::Bullet()
	{
		bulletState = 1;
		fireReady = true;
	}

	Bullet::~Bullet() {};

	void Bullet::BulletMechanics(int playerX, int playerY) {

		switch (bulletState) {
		case 1: BulletFollowPlayer(playerX, playerY);
			break;
		case 2: BulletFired();
			break;
		}
	}

	void Bullet::BulletFired(){
		
		fireReady = false;
		y--;

		if (y < 0) {
			bulletState = 1;
			fireReady = true;
		}

		// Enemy Resolution: 11 x 8
		//Bullet Resolution 1 x 6

	}


	void Bullet::BulletDraw(Tmpl8::Surface* screen) {

			screen->Box(x, y - 1, x, y + 4, 0xffff00);
		}

	void Bullet::BulletFollowPlayer(int playerX, int playerY) {
			x = playerX + 6;
			y = playerY;
			fireReady = true;
	}

	void Bullet::ResetAfterHit(int i) {
		fireReady = true;
		SetBulletState(i);
	}
 
 	 void Bullet::SetBulletState(int i) { if (fireReady) bulletState = i; }

	int Bullet::getX() { return x; }
	int Bullet::getY() { return y; }

