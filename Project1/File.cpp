#include "File.h"

File::File() {

}

File::File(const char* file)
{
	reader.open(file);
	if (!reader.is_open())
	{
		SDL_Log("map not found");
		exit(EXIT_FAILURE);
	}
	char num;
	reader >> num;
	while (reader.good())
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				int c = num - 48;//convert to int
				Map[i][j] = c;
				//cout << Map[i][j];
				reader >> num;
			}
			//cout << endl;
		}
		break;
	}
}

File::File(int num)
{
	num = num;
}

File::~File()
{
}
