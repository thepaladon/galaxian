#include "game.h"
#include "surface.h"
#include "template.h"

#include "player.h"
#include "enemy.h"
#include "bullet.h"

#include <cstdio> 
#include <windows.h>
#include <time.h>
#include <corecrt_math.h>
#include <cstdio> //printf

#define NUMSTARS 100
#define NUMENEMIES 30

//256, 224 resolution of the original Galaxian screen
// Player Resolution: 30 x 13
// Enemy Resolution: 11 x 8
//Bullet Resolution 1 x 6


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
	Enemy enemy[NUMENEMIES];
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
		int ex = 1;
		int wy = 1; 

		for (int i = 0; i < NUMENEMIES; i++) {
			
			if(i % 10 == 0) {
				wy = wy + 1;
				ex = 1;
			}
			printf("%i %i %i \n", i, ex, wy);
			enemy[i].SetCoords(maxMovementOfEnemyCluster + ex * 15, wy * 10 );
			ex = ex + 1;
		}
	}
	
	void Game::Shutdown()
	{

	}

	static Sprite playerAsset(new Surface("assets/galaxianship.png"), 1);
	static Sprite greenEnemy(new Surface("assets/greenenemy.png"), 1);

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
		for (int i = 0; i < NUMENEMIES; i++) {
			if (!enemy[i].GetAliveState()) {
				enemy[i].EnemyCollision(&bullet);
				enemy[i].EnemyMechanics(directionGoingRight, maxMovementOfEnemyCluster);
				greenEnemy.Draw(screen, enemy[i].GetX(), enemy[i].GetY());
				screen->Line(enemy[i].GetX(), enemy[i].GetY(), enemy[i].GetX(), enemy[i].GetY(), 0xff0000);
			}
		}

		for(int i =0; i < 10; i++)
		bullet.BulletMechanics(player.getX(), player.getY());

		// Neat pointer explanation by Phil
		/*int a = 10;
		int* b = &a;
		int** c = &b;
		printf("%i", **c);*/

		//Temporary solution
		if (GetAsyncKeyState(VK_LEFT)) player.PlayerControlLeft();
		if (GetAsyncKeyState(VK_RIGHT)) player.PlayerControlRight();
		if (GetAsyncKeyState(VK_SPACE)) bullet.SetBulletState(2);

		bullet.BulletDraw(screen);


		Sleep(10);
		printf("Enemy 0 Coords: %i %i \n", enemy[0].GetX(), enemy[0].GetY());
		
	}

	void EnemyCheck() {
		int mostLeftX = 100;
		int mostRightX = 100;

		for (int i = 0; i < NUMENEMIES; i++) {
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