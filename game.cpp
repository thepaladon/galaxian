#include "game.h"
#include "surface.h"
#include <cstdio> //printf

#include <cstdio> 
#include <windows.h>
#include <time.h>

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
		screen->Box(x - 5, y - 10, x + 5, y + 10, 0xff0000);
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

	void BulletMechanics(int playerX, int playerY) {
		
		switch(bulletState) {
		case 1: BulletFollowPlayer(playerX, playerY);
			break;
		case 2: BulletFired();
			break;
		}
	}

	void BulletFired() {
		fireReady = false;

		y--;
		printf("Fire");

		if (y < 0) {
			bulletState = 1;
			fireReady = true;
		}
	}

	void BulletDraw(Tmpl8::Surface* screen) {
		screen->Box(x - 2, y - 4, x + 2, y + 4, 0xffff00);
	}

	void BulletFollowPlayer(int playerX, int playerY) {
		x = playerX;
		y = playerY;
		fireReady = true;
	}

	void SetBulletState(int i) { if (fireReady) bulletState = i; }

private:
	int x, y;
	int bulletState = 1; // 1 - follows player; 2 - is firing; 3 - is reseting;
	bool fireReady = true;
};


namespace Tmpl8
{
	
	void Game::Init()
	{
	}
	
	void Game::Shutdown()
	{

	}

	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);

	int timeElapsed;
	int timer;
	Star stars[NUMSTARS];
	Player player;
	Bullet bullet;
	static int frame = 0;

	/*void Game::KeyDown(int key) {

		switch (key) {
		case 80: player.PlayerControlLeft();
			break;
		case 79:player.PlayerControlRight();
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

		player.DrawPlayer(screen);
		if (GetAsyncKeyState(VK_LEFT)) player.PlayerControlLeft(); 
		if (GetAsyncKeyState(VK_RIGHT)) player.PlayerControlRight();
		if (GetAsyncKeyState(VK_SPACE)) bullet.SetBulletState(2);

		bullet.BulletDraw(screen);
		bullet.BulletMechanics(player.getX(), player.getY());


		rotatingGun.SetFrame(frame);
		rotatingGun.Draw(screen, 100, 100);
		if (++frame == 36) frame = 0;

		Sleep(0);
	}


};