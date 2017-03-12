#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h" 
#include "include\SDL_mixer.h"
#include "Player.h"
#include "Control.h"

#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

Player player;

using namespace std;

SDL_Window *window;
SDL_Renderer* renderer;
SDL_Event event;

vector<Control> Controller;

string nums[11] = { "Score: ","1","2","3","4","5","6","7","8","9","0" };
int numbers[10];
int rendernums[10][10];

bool running = true;
bool keyPress = false;
double delta_time, old_time;
const double FPS = 60.0;


void ToggleFullscreen(SDL_Window* wind);
double current_time();
SDL_Texture* loadFont(string file, int fontsize, string text, int r, int g, int b, int o);

void update()
{

}

void process_input()
{
	while (SDL_PollEvent(&event))//can use switch statements for multiple options
	{
		//handle event here
		if (event.type == SDL_QUIT)//if you click the x on the top right
		{
			running = false;//quits
		}
		else if (event.type == SDL_KEYDOWN)
		{

			//select surcases bases on key press
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				running = false;
				break;
				//--------------------
				//music
				//---------------------------------------------------
				//movement
				//-----------------------------------------------------
			case SDLK_RETURN:
				if (event.key.keysym.mod & KMOD_LALT)
					ToggleFullscreen(window);
				break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			keyPress = false;
		}
	}
}

void render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderClear(renderer);//need to clear before displaying	
	SDL_RenderPresent(renderer);
}

void createFonts(char* filename)
{
	ifstream reader;
	reader.open(filename);
	if (!reader.is_open())
	{
		SDL_Log("map not found");
		exit(EXIT_FAILURE);
	}
	char num;
	reader >> num;
	while (reader.good())
	{
		for (int i = 0; i < 10; i++)
		{
			int c = num - 48;//convert to int
			numbers[i] = c;
			//cout << numbers[i] << endl;
			reader >> num;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			rendernums[i][j] = numbers[j];
			//cout << rendernums[i][j] << endl;
		}
	}
}
void fillFonts(vector<Control> ct)
{
	for (int i = 0; i < 11; i++)
	{
		SDL_Texture* font = loadFont("XBR.ttf", 15, nums[i], 0, 0, 0, 255);
		if (font == nullptr)
		{
			SDL_Log("an error has occured creating fonts");
		}
		ct.emplace_back(font);
	}
}

void ToggleFullscreen(SDL_Window* wind)
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
	bool isFull = SDL_GetWindowFlags(wind) & FullscreenFlag;
	SDL_SetWindowFullscreen(wind, isFull ? 0 : FullscreenFlag);
	SDL_ShowCursor(isFull);
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow("Sweet Maze", SDL_WINDOWPOS_CENTERED/*x*/, SDL_WINDOWPOS_CENTERED/*y*/,
		1000/*w*/, 700/*h*/, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, (SDL_RENDERER_ACCELERATED));//-1 becuase there is no index
																	 
	if (TTF_Init() == -1) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_ttf init error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL_ttf initialised OK!\n");

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		cout << IMG_GetError() << endl;
		SDL_Log(IMG_GetError());
	}
	if (TTF_Init() < 0)
	{
		SDL_GetError();
	}

	createFonts("numbers.txt");
	fillFonts(Controller);

	old_time = current_time();

	while (running) {
		delta_time = current_time() - old_time;
		if (delta_time > 1000.0 / FPS) {

			process_input();
			update();
			render();

			old_time = current_time();
		}
		else {
			SDL_Delay(1);
		}
	}

	//SDL_FreeSurface();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	IMG_Quit();
	//TTF_CloseFont();//needs to be font in here to close
	TTF_Quit();
	Mix_Quit();
	return 0;
}

double current_time() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

SDL_Texture* loadFont(string file, int fontsize, string text, int r, int g, int b, int o)// add a way to change score
{
	if (r > 255 || g > 255 || b > 255 || o > 255)
	{
		cout << "cannot be greater than 255" << endl;
		SDL_Log("there cannot be a rgbo value greater than 255");
	}
	else if (r < 0 || g < 0 || b < 0 || o < 0)
	{
		cout << "cannot be lower than 0" << endl;
		SDL_Log("there cannot be a rgbo value lower than 0");
	}
	else {
		TTF_Font* font = TTF_OpenFont(file.c_str(), fontsize);
		SDL_Color colour = { r,g,b,o };
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), colour);
		SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
		textSurface = nullptr;
		SDL_QueryTexture(fontTexture, NULL, NULL, NULL, NULL);
		return  fontTexture;
	}

}