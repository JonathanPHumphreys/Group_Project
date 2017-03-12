#include "Obstacles.h"



Obstacles::Obstacles()
{
}

void Obstacles::init_Rect(SDL_Rect & rect, int x, int y, int w, int h)
{
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
}

void Obstacles::setValue(int amount)
{
	value = amount;
}

Obstacles::~Obstacles()
{
}
