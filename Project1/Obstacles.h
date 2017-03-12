#pragma once
#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h" 
#include "include\SDL_mixer.h"

class Obstacles
{
public:
	Obstacles();
	//funcitons
	void init_Rect(SDL_Rect &rect, int x, int y, int w, int h);
	~Obstacles();
	//variables
	SDL_Texture* Wall;
	SDL_Texture* Collectible;
	SDL_Rect wall_destination;
	SDL_Rect coll_destination;
	int score = 0;
};

