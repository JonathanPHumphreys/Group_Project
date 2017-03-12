#pragma once
#include "constants.h"

class Player
{
public:
	Player();
	//functions
	Player(SDL_Texture* INIT_TEXT);//initialise texture 
	void init_Rect(SDL_Rect &rect ,int x, int y, int w, int h);
	void addScore(int whatToAdd);

	~Player();
	//variables
	SDL_Texture* playerTexture;
	SDL_Texture* endPoint;
	SDL_Surface playerSurface;
	SDL_Rect destination;
	int score = 0;

};

