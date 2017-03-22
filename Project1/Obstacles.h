#pragma once
#include "constants.h"

class Obstacles
{
public:
	Obstacles();
	Obstacles(SDL_Texture* INIT_TEXT);
	Obstacles(SDL_Texture* INIT_TEXT, int INIT_VALUE);
	SDL_Rect INIT_rects(SDL_Rect rect, bool plr, int x, int y);
	//funcitons
	~Obstacles();
	//variables
	SDL_Texture* Wall;
	SDL_Texture* Wall_red;
	SDL_Texture* Wall_yellow;
	SDL_Texture* Wall_green;
	SDL_Texture* Wall_blue;
	SDL_Texture* Wall_purple;
	SDL_Texture* Collectible;
	SDL_Rect wall_destination;
	SDL_Rect candy_destination;
	
	int Map[10][10];
	int value = 0;
	int w_h = 50;
	int offsetX = 100;
	int offsetY = 100;
};

