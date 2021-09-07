#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <stdlib.h>
#define NUMSTARS 100

//256, 224 resolution of the original Galaxian screen

namespace Tmpl8
{
	int starsX[NUMSTARS], starsY[NUMSTARS];
	void Game::Init()
	{
		for (int i = 0; i < NUMSTARS; i++) {
			starsX[i] = rand() % 256;
			starsY[i] = rand() % 224;
		}
		
	}
	

	void Game::Shutdown()
	{

	}

	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;
	int starTracker;

	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		//screen->Clear(0);
		// print something in the graphics window
		screen->Print("hello world", 2, 2, 0xffffff);
		// print something to the text window
		printf("this goes to the console window.\n");
		// draw a sprite
		rotatingGun.SetFrame(frame);
		rotatingGun.Draw(screen, 100, 100);
		if (++frame == 36) frame = 0;

		for (int i = 0; i < NUMSTARS; i++) {
			screen->Line(starsX[i], starsY[i], starsX[i], starsY[i], 0xfffffff);
		}
	}
};