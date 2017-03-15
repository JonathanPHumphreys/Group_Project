#pragma once
#include "constants.h"

class Obstacles
{
public:
	Obstacles();
	Obstacles(SDL_Texture* INIT_TEXT);
	Obstacles(SDL_Texture* INIT_TEXT, int INIT_VALUE);
	//funcitons
	void init_Rect(SDL_Rect &rect, int x, int y, int w, int h);
	~Obstacles();
	//variables
	SDL_Texture* Wall;
	SDL_Texture* Collectible;
	SDL_Rect wall_destination;
	SDL_Rect candy_destination;
	
	int Map[10][10];
	int value = 0;
};

