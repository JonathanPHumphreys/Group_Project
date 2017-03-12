#pragma once
#include "constants.h"



class File {
	ifstream map_data_in;
public:
	int map_data [28][31];
	File();
};