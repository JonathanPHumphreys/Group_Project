#include "Obstacles.h"
#include "Player.h"

Obstacles::Obstacles()
{
}

Obstacles::Obstacles(SDL_Texture * INIT_TEXT)
{
	Wall = INIT_TEXT;
	//wall_destination = { x, y, w_h, w_h};
	// << wall_destination.x << wall_destination.y << wall_destination.w << wall_destination.h << endl;
}

Obstacles::Obstacles(SDL_Texture* INIT_TEXT, int INIT_value)
{
	value = INIT_value;
	Collectible = INIT_TEXT;
	//candy_destination = { x, y, w_h, w_h };
	//cout << candy_destination.x <<  candy_destination.y <<  candy_destination.w << candy_destination.h << endl;
}

SDL_Rect Obstacles::INIT_rects(SDL_Rect rect, bool plr, int x, int y)
{
	
	if (plr == false )
	{
		rect = { x,y,w_h,w_h };
	}
	else
	{
		rect = { x, y };
	}
	//cout << rect.x << " " << rect.y << " "<< rect.w << " " << rect.h << endl;
	return rect;
}

Obstacles::~Obstacles()
{

}
