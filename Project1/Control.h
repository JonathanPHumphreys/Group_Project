#pragma once
#include "constants.h"

class Control
{
public:
	Control();
	Control(SDL_Texture* font_input);
	~Control();
	SDL_Texture* font;
};