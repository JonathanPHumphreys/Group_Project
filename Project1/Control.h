#pragma once
#include "constants.h"

class Control
{
public:
	Control();
	Control(SDL_Texture* font_input);
	~Control();
	SDL_Texture* font;
	SDL_Color white = { 225,255,255,255 };
	SDL_Color black = { 0,0,0,255 };
	SDL_Color red = { 225,0,0,255 };
	SDL_Color blue = { 0,255,0,255 };
	SDL_Color green = { 0,0,255,255 };
};