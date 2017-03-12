#include "File.h"

File::File() {
	map_data_in.open("assets/map.txt");
	char c;
	int num;

	for (int i = 0; i < map_data.size(); i++) {
		for (int j = 0; j < map_data[i].size() && map_data_in.get(c); j++) {
			num = c - '0';
			map_data[i][j] = num;
		}
	}
}