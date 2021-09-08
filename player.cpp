#include "player.h"
#include "surface.h"

	Player::Player()
	{
		int x = 100;
		int y = 200;
	}

	Player::~Player() {};

	void Player::PlayerControlLeft()
	{
		x--;
	}
	void Player::PlayerControlRight()
	{
		x++;
	}

	void Player::DrawPlayer(Tmpl8::Surface* screen) {
		KeepPlayerInside();
	}

	void Player::KeepPlayerInside() {
		if (x < 10) {
			x = 10;
		}

		if (x > 246) {
			x = 246;
		}
	}

	int Player::getX() { return x; }
	int Player::getY() { return y; }

