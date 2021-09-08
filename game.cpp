#include "game.h"
#include "surface.h"
#include "template.h"


#include <cstdio> 
#include <windows.h>
#include <time.h>
#include <corecrt_math.h>
#include <cstdio> //printf

#define NUMSTARS 100

//256, 224 resolution of the original Galaxian screen

class Star
{
public:
	Star()
	{
		starsX = rand() % 256;
		starsY = rand() % 224;
		starSwitch = rand() % 2;
		starColor = rand() % 16777216;
	}

	void StarUpdate(Tmpl8::Surface* screen){

		if (starSwitch)
			screen->Line(starsX, starsY, starsX, starsY, starColor);

		starsY++; //star moves down

		if (starsY > 224) //height
			starsY = 0;
	}

	void ChangeState() {
		if (starSwitch) {
			starSwitch = false;
		}
		else if (!starSwitch) {
			starSwitch = true;
		}
	}

	void StarTimer(int timeElapsed) {
		if (timeElapsed % 1000 < 500) { 
			ChangeState();
		}
		
	}

private:
	int starsX;
	int starsY;
	int starEnabler;
	bool starSwitch;
	int starColor;

};

class Player
{
public:
	Player()
	{
		int x = 100;
		int y = 200;
	}

	void PlayerControlLeft()
	{
		x--;
	}
	void PlayerControlRight()
	{
		x++;
	}

	void DrawPlayer(Tmpl8::Surface* screen) {
		KeepPlayerInside();
	}

	void KeepPlayerInside() {
		if (x < 10) {
			x = 10;
		}

		if (x > 246) {
			x = 246;
		}
	}

	int getX() const { return x; }
	int getY() const { return y; }


private:
	int x = 100;
	int y = 200;
};

class Bullet {
public:
	Bullet()
	{
		bulletState = 1;
		fireReady = true;
	}

	void BulletMechanics(int playerX, int playerY, int enemyX, int enemyY) {
		
		switch(bulletState) {
		case 1: BulletFollowPlayer(playerX, playerY);
			break;
		case 2: BulletFired(enemyX, enemyY);
			break;
		}
	}

	void BulletFired(int enemyX, int enemyY) {
		fireReady = false;

		y--;
		printf("Fire");

		if (y < 0) {
			bulletState = 1;
			fireReady = true;
		}

		//if (x < enemyX + rect2.width &&
		//	rect1.x + rect1.width > rect2.x &&
		//	rect1.y < rect2.y + rect2.height &&
		//	rect1.y + rect1.height > rect2.y) {
		//	// collision detected!
		//}

	}

	void BulletDraw(Tmpl8::Surface* screen) {
		screen->Box(x, y-1, x, y+4, 0xffff00);
	}

	void BulletFollowPlayer(int playerX, int playerY) {
		x = playerX + 6;
		y = playerY;
		fireReady = true;
	}

	void SetBulletState(int i) { if (fireReady) bulletState = i; }

	int getX() const { return x; }
	int getY() const { return y; }

private:
	int x, y;
	int bulletState = 1; // 1 - follows player; 2 - is firing; 3 - is reseting;
	bool fireReady = true;
};

class Enemy {
public:
	Enemy() {
		x = 100;
		y = 20;
		stateOfEnemy = 1;
		directionGoingLeft = true;
	}

	void DrawEnemy(Tmpl8::Surface* screen) {
		screen->Box(x - 8, y - 8, x + 8, y + 8, 0xff00ff);
	}

	void IdleAnimation(bool directionGoingRight, int max) {
		if (directionGoingRight) 
			x++;
		else if (!directionGoingRight) 
			x--;
	}

	void EnemyMechanics(bool directionGoing, int max) {
		switch (stateOfEnemy) {
		case 1: IdleAnimation(directionGoing, max);
			break;
		case 2: 
			break;
		}

	}

	void SetCoords(int Ex, int Wy) { x = Ex; Wy = y; }
	int GetX() { return x; }
	int GetY() { return y; }
	

private:
	int x, y;
	int stateOfEnemy; // 1 - idle in group, 2 - attacking
	int directionGoingLeft = true;
	bool enemyDead;

};

namespace Tmpl8
{
	int timeElapsed;
	int timer;

	int maxMovementOfEnemyCluster = 28; //those variables refer to the end points to which the enemies are allowed to move.
	 //one there are fewer enemies there are allowed to move moree to the right and left.
	bool directionGoingRight;

	Star stars[NUMSTARS];
	Player player;
	Bullet bullet;
	Enemy enemy[10];
	static int frame = 0;

	int m = -16;

	void EnemyCheck();

	//experiments for creating the curve
	void Circle(Surface* s, float x, float y, float r)
	{
			float r1 = (float)m * PI / 32, r2 = (float)(m) * PI / 32;
			int finalx = x - r * sinf(r1);
			int finaly = y - r * cosf(r1);
			m++;

			if (m > 16) {
				m = -16;
			}

			s->Box(finalx - 5, finaly - 5, finalx + 5, finaly + 5, 0xFFFFFf);
	}

	void Game::Init()
	{
		//Initialising green enemies
		for (int i = 0; i < 10; i++) {
			enemy[i].SetCoords(28 + i * 20, 20);
		}
	}
	
	void Game::Shutdown()
	{

	}

	static Sprite playerAsset(new Surface("assets/galaxianship.png"), 1);


	
	//This works but it's way slower and also ignores the SPACE key [it only allows for one input]
	/*void Game::KeyDown(int key) {

		switch (key) {
		case 80: player.PlayerControlLeft();
			break;
		case 79:player.PlayerControlRight();
			break;
		case 57: bullet.SetBulletState(2);

		}
	}*/

	void Game::Tick(float deltaTime)
	{
		srand(time(NULL));

		timeElapsed = timeElapsed + deltaTime;
		
		screen->Clear(0);

		screen->Print("hello world", 2, 2, 0xffffff);
		//Maybe ask LEVI how to work with hexadecimal numbers
				
		for (int i = 0; i < NUMSTARS; i++) {
			stars[i].StarUpdate(screen);
			stars[i].StarTimer(timeElapsed);
		}
		Circle(screen, 50, 50, 50);
		if (GetAsyncKeyState(VK_CONTROL)) m++;

		playerAsset.Draw(screen, player.getX(), player.getY());

		player.DrawPlayer(screen);

		EnemyCheck();
		for (int i = 0; i < 10; i++) {
			enemy[i].DrawEnemy(screen);
			enemy[i].EnemyMechanics(directionGoingRight, maxMovementOfEnemyCluster);
			bullet.BulletMechanics(player.getX(), player.getY(), enemy[i].GetX(), enemy[i].GetY());

		}

		//Temporary solution
		if (GetAsyncKeyState(VK_LEFT)) player.PlayerControlLeft();
		if (GetAsyncKeyState(VK_RIGHT)) player.PlayerControlRight();

		printf("%i \n", maxMovementOfEnemyCluster);

		if (GetAsyncKeyState(VK_SPACE)) bullet.SetBulletState(2);

		bullet.BulletDraw(screen);


		Sleep(10);

		
	}

	void EnemyCheck() {
		int mostLeftX = 100;
		int mostRightX = 100;
		for (int i = 0; i < 10; i++) {
			if (enemy[i].GetX() < mostLeftX) {
				mostLeftX = enemy[i].GetX();
			}

			if (enemy[i].GetX() > mostRightX) {
				mostRightX = enemy[i].GetX();
			}
			
		}

		if (mostRightX > 256 - maxMovementOfEnemyCluster) {
			directionGoingRight = false;
		}
		else if (mostLeftX < maxMovementOfEnemyCluster) {
			directionGoingRight = true;
		}

	}

};