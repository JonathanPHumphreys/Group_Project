#include "Player.h"

Player::Player()
{
}

Player::Player(SDL_Texture * INIT_TEXT)
{
	playerTexture = INIT_TEXT;
}

void Player::init_Rect(SDL_Rect & rect, int x, int y, int w, int h)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

Player::~Player()
{
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(endPoint);
	SDL_DestroyTexture(scoreText);
	SDL_DestroyTexture(numbersText);
	playerSurface = nullptr;
	SDL_FreeSurface(playerSurface);
}

bool Player::is_colliding(SDL_Rect &a, SDL_Rect &b) {
	bool collision = true;

	if (a.y + a.h <= b.y) {
		collision = false;
	}
	else if (a.y >= b.y + b.h)
	{
		collision = false;
	}
	else if (a.x + a.w <= b.x)
	{
		collision = false;
	}
	else if (a.x >= b.x + b.w)
	{
		collision = false;
	}

	return collision;
}
