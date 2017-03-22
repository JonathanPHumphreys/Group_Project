#include "constants.h"
#include "Player.h"
#include "Control.h"
#include "Obstacles.h"
#include "File.h"

Player player;
Obstacles Ob;
Control Con;
File F("map1.txt");

vector<Control> ControlVec;
vector<Obstacles> ObVec;

using namespace std;

SDL_Window *window;
SDL_Renderer* renderer;
SDL_Event event;

int direction = 0;
bool running = true;
bool keyPress = false;
double delta_time, old_time;
const double FPS = 60.0;
int row = 15;

double current_time();
void ToggleFullscreen(SDL_Window* wind);
SDL_Texture* createFont(TTF_Font* font, const char* whatTheFontIs,  SDL_Texture* whereToStore);
void createTexture(int amountOfObject, const char* file, vector<Obstacles> Ob);
void createTexture(int amountOfObject, const char* file, vector<Obstacles> Ob, int valueForCandy);
void createNumberFont(vector<Control> &newvector, SDL_Texture* texture, TTF_Font* font);
void storeTextures(vector<Obstacles> &vectorObj, Player plr);

void update()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (F.Map[i][j] == 1 && player.is_colliding(player.destination, Ob.INIT_rects(Ob.wall_destination, false, Ob.offsetX, Ob.offsetY)))
			{
				switch (direction)
				{
				case 1:
					player.destination.x = player.destination.x + 5;
					break;
				case 2:
					player.destination.y = player.destination.y + 5;
					break;
				case 3:
					player.destination.x = player.destination.x - 5;
					break;
				case 4:
					player.destination.y = player.destination.y - 5;
					break;
				}
			}
			else if (F.Map[i][j] == 2 && player.is_colliding(player.destination, Ob.INIT_rects(Ob.candy_destination, false, Ob.offsetX, Ob.offsetY)))
			{
				// add to score? or something
			}
			else
			{
				//cout << "out of reach in creation of Map detected::::" << endl;
			}
			Ob.offsetX += 50;
		}
		Ob.offsetX = 100;
		Ob.offsetY += 50;
	}
	Ob.offsetX = 100;
	Ob.offsetY = 100;
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
				//movement : TODO - make smooth and in relation to delta time
			case SDLK_UP:
				keyPress = true;
				direction = 2;
				player.destination.y = player.destination.y - 5;
				break;
			case SDLK_DOWN:
				keyPress = true;
				direction = 4;
				player.destination.y = player.destination.y + 5;
				break;
			case SDLK_LEFT:
				keyPress = true;
				direction = 1;
				player.destination.x = player.destination.x - 5;
				break;
			case SDLK_RIGHT:
				keyPress = true;
				direction = 3;
				player.destination.x = player.destination.x + 5;
				break;
				//-----------------------------------------------------
			case SDLK_f:
				player.score1++;//TODO: ADD SCORE
				break;

			case SDLK_RETURN:
				if (event.key.keysym.mod & KMOD_LALT)
					ToggleFullscreen(window);
				break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			keyPress = false;
			direction = 0;
		}
	}
}

void render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderClear(renderer);//need to clear before displaying	

	if (player.scoreText = nullptr)
	{
		cout << "score text is nullptr" << endl;
	}

	if (player.score1 > 9)
	{
		if (player.score0 > 9)
		{
			//cannot be past 99 - TODO: CONDITION
			player.score0 = 0;
			player.score1 = 0;
		}
		player.score1 = 0;
		player.score0++;
	}

	SDL_RenderCopy(renderer, player.scoreText, NULL, &player.scoreRect);
	if (player.scoreText = nullptr)
	{
		cout << "score text is null" << endl;
	}
	SDL_RenderCopy(renderer, ControlVec[0 + player.score0].font, NULL, &player.numberRect0);
	SDL_RenderCopy(renderer, ControlVec[0 + player.score1].font, NULL, &player.numberRect1);
	SDL_RenderCopy(renderer, player.playerTexture, NULL, &player.destination);
	if (player.playerTexture = nullptr)
	{
		cout << "player is nullptr" << endl;
	}

	//check to see if the texture is nullptr, if not then display
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (F.Map[i][j] == 0)
			{
				//blank space
			}
			else if (F.Map[i][j] == 1)
			{
				SDL_RenderCopy(renderer, ObVec[i * row  + j].Wall, NULL, &Ob.INIT_rects(Ob.wall_destination, false, Ob.offsetX, Ob.offsetY));
			}
			else if (F.Map[i][j] == 2)
			{
				SDL_RenderCopy(renderer, Ob.Collectible, NULL, &Ob.INIT_rects(Ob.candy_destination, false, Ob.offsetX, Ob.offsetY));
			}
			else if (F.Map[i][j] == 3)
			{
				SDL_RenderCopy(renderer, player.playerTexture, NULL, &Ob.INIT_rects(player.destination, true, Ob.offsetX, Ob.offsetY));
			}
			else
			{
				//cout << "out of reach in creation of Map detected::::" << endl;
			}
			Ob.offsetX += 50;
		}
		Ob.offsetX = 100;
		Ob.offsetY += 50;
	}
	Ob.offsetX = 100;
	Ob.offsetY = 100;
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
	srand(time(NULL));
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

	player.playerTexture = IMG_LoadTexture(renderer, "ball.png");
	if (player.playerTexture == nullptr)
	{
		cout << "player texture is null" << endl;
	}
	player.init_Rect(player.destination, 655 ,505, 40, 40);
	player.checkRects();

	storeTextures(ObVec, player);

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

	//delete &player;

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

void createTexture(int amountOfObject, const char * file, vector<Obstacles> Ob)
{
	SDL_Texture* tmpTex = IMG_LoadTexture(renderer, file);
	for (int i = 0; i < amountOfObject; i++)
	{
		Ob.emplace_back(tmpTex);
	}
}

void createTexture(int amountOfObject, const char * file, vector<Obstacles> Ob, int valueForCandy)
{
	SDL_Texture* tmpTex = IMG_LoadTexture(renderer, file);
	for (int i = 0; i < amountOfObject; i++)
	{
		Ob.emplace_back(tmpTex, valueForCandy);
	}
}

void createNumberFont(vector<Control>& newvector, SDL_Texture* texture, TTF_Font* font)
{

	for (int i = 0; i < 10; i++)
	{
		//cout << player.numbers[i] << endl;
		SDL_Surface *textSurface = TTF_RenderText_Solid(font, player.numbers[i], Con.black);
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textSurface = nullptr;
		SDL_FreeSurface(textSurface);
		newvector.emplace_back(texture);
	}
}

void storeTextures(vector<Obstacles> &vectorObj, Player plr)
{
	int random;
	Ob.Wall_red = IMG_LoadTexture(renderer, "redblock.png");
	Ob.Wall_blue = IMG_LoadTexture(renderer, "blueblock.png");
	Ob.Wall_purple = IMG_LoadTexture(renderer, "purpleblock.png");
	Ob.Wall_green = IMG_LoadTexture(renderer, "greenblock.png");
	Ob.Wall_yellow = IMG_LoadTexture(renderer, "yellowblock.png");
	Ob.Collectible = IMG_LoadTexture(renderer, "sweets.png");
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			random = rand()%  5 + 0;//between 0 and 5;;
			if (F.Map[i][j] == 0)
			{
				vectorObj.emplace_back();
			}
			else if (F.Map[i][j] == 1)
			{
				//walls
				
				if (random == 0)
				{
					//go red
					vectorObj.emplace_back(Ob.Wall_red);
				}
				else if (random == 1)
				{
					vectorObj.emplace_back(Ob.Wall_purple);
				}
				else if (random == 2)
				{
					vectorObj.emplace_back(Ob.Wall_blue);
				}
				else if (random == 3)
				{
					vectorObj.emplace_back(Ob.Wall_green);
				}
				else if (random == 4)
				{
					vectorObj.emplace_back(Ob.Wall_yellow);
				}
				else
				{
					cout << "this should not occur" << endl;
				}
			}
			else if (F.Map[i][j] == 2)
			{
				//collectible
				vectorObj.emplace_back();
			}
			else if (F.Map[i][j] == 3)
			{
				//player
				vectorObj.emplace_back();

			}
			else {
				cout << "this is out of bounds" << endl;
			}
			
		}
	}
}
