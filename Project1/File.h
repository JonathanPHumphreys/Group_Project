#pragma once
#include "constants.h"



class File {
	ifstream map_data_in;
public:
	array<array<int, 28>, 31> map_data;
	File();
};