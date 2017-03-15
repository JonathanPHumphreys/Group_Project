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
	SDL_Texture* scoreText;
	SDL_Texture* numbersText;
	SDL_Surface playerSurface;
	SDL_Rect destination;
	SDL_Rect scoreRect = { 5,5, 30, 30 };
	SDL_Rect numbeRect = { 15,5, 30, 30 };
	int score = 0;
	int numbers[10] = { 0,1,2,3,4,5,6,7,8,9 };//for displaying the player score.
};

