#include "Obstacles.h"

Obstacles::Obstacles()
{
}

Obstacles::Obstacles(SDL_Texture * INIT_TEXT)
{
	Wall = INIT_TEXT;
}

Obstacles::Obstacles(SDL_Texture* INIT_TEXT, int INIT_value)
{
	value = INIT_value;
	Collectible = INIT_TEXT;
}

void Obstacles::init_Rect(SDL_Rect & rect, int x, int y, int w, int h)
{
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
}

Obstacles::~Obstacles()
{
}
