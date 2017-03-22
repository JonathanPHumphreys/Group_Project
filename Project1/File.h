#pragma once
#include "constants.h"

class File {
	ifstream reader;
public:
	File();
	File(const char* file);
	File(int num);
	~File();
	
	int Map[11][15];
	char c = '0';
	int num = 0;
private:

};