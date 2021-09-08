#include "surface.h"
class Player
{
public:
	Player();
	~Player();
	void PlayerControlLeft();
	void PlayerControlRight();
	void DrawPlayer(Tmpl8::Surface* screen);
	void KeepPlayerInside();
	int getX();
	int getY();

private:
	int x = 100;
	int y = 200;
};
