#pragma once
#include "constants.h"

class Obstacles
{
public:
	Obstacles();
	//funcitons
	void init_Rect(SDL_Rect &rect, int x, int y, int w, int h);
	void setValue(int amount);
	~Obstacles();
	//variables
	SDL_Texture* Wall;
	SDL_Texture* Collectible;
	SDL_Rect wall_destination;
	SDL_Rect coll_destination;
	SDL_Color white = { 225,255,255,255 };
	SDL_Color black = { 0,0,0,255 };
	SDL_Color red = { 225,0,0,255 };
	SDL_Color blue = { 0,255,0,255 };
	SDL_Color green = { 0,0,255,255 };


	int Map[10][10];
	int value = 0;
};

