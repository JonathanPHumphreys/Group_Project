#pragma once
#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h" 
#include "include\SDL_mixer.h"

class Control
{
public:
	Control();
	Control(SDL_Texture* font_input);
	~Control();
	SDL_Texture* font;
};

