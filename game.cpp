#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	int starsX[50], starsY[50];
	void Game::Init()
	{

		for (int x = 0; x < 50; x++) {
			for (int y = 0; x < 50; y++) {
				starsX[x] += x * y;
				starsY[x] += x * y;
			}
		}
	}
	

	void Game::Shutdown()
	{

	}

	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;
	

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

		for (int i = 0; i < 50; i++) {
			screen->Line(starsX[i], starsY[i], starsX[i], starsY[i], 0xfffffff);
		}
	}
};