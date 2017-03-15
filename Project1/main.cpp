#include "constants.h"
#include "Player.h"
#include "Control.h"
#include "Obstacles.h"

Player player;
Obstacles Ob;
Control Con;

vector<Control> ControlVec;

using namespace std;

SDL_Window *window;
SDL_Renderer* renderer;
SDL_Event event;


bool running = true;
bool keyPress = false;
double delta_time, old_time;
const double FPS = 60.0;


void ToggleFullscreen(SDL_Window* wind);
double current_time();
SDL_Texture* createFont(TTF_Font* font, const char* whatTheFontIs,  SDL_Texture* whereToStore);
void createNumberFont(vector<Control> &newvector, SDL_Texture* texture, TTF_Font* font);

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
	SDL_RenderCopy(renderer, player.scoreText, NULL, &player.scoreRect);
	SDL_RenderPresent(renderer);
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

	old_time = current_time();
	TTF_Font *font = TTF_OpenFont("XBR.ttf", 30);
	
	player.scoreText = createFont(font, "Score: ", player.scoreText);
	
	createNumberFont(ControlVec, Con.font, font);

	SDL_QueryTexture(player.scoreText, NULL, NULL, &player.scoreRect.w, &player.scoreRect.h);


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

	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	IMG_Quit();
	TTF_CloseFont(font);//needs to be font in here to close
	TTF_Quit();
	Mix_Quit();
	return 0;
}

double current_time() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

SDL_Texture* createFont(TTF_Font * font, const char * whatTheFontIs ,SDL_Texture * whereToStore)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, whatTheFontIs, Con.black);
	SDL_Texture* newt = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = nullptr;
	SDL_FreeSurface(textSurface);
	return newt;
}

void createNumberFont(vector<Control>& newvector, SDL_Texture* texture, TTF_Font* font)
{

	for (int i = 0; i < 10; i++)
	{
		cout << player.numbers[i] << endl;
		SDL_Surface *textSurface = TTF_RenderText_Solid(font, player.numbers[i], Con.black);
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textSurface = nullptr;
		SDL_FreeSurface(textSurface);
		newvector.emplace_back(texture);
	}
}
