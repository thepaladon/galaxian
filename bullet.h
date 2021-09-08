#pragma once  //file should ever only be inlcuded once
#include "surface.h"

class Bullet
{
public:
	Bullet();
	~Bullet(); //to clean up when a class dies
	void BulletMechanics(int playerX, int playerY, int enemyX, int enemyY, bool enemyDeath);
	void BulletFired(int enemyX, int enemyY, bool enemyDeath);
	void BulletDraw(Tmpl8::Surface * screen);
	void BulletFollowPlayer(int playerX, int playerY);
	void SetBulletState(int i);
	int getX();
	int getY();

private:
	int x, y;
	int bulletState = 1; // 1 - follows player; 2 - is firing; 3 - is reseting;
	bool fireReady = true;

};

