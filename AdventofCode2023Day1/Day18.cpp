#include "./headers/Day18.h"

int Day18::day() {
	std::string line;
	std::fstream file("./inputs/day18input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;
	}

	//factory needs a lagoon of lava in reserve
	//we are given digging plans
	//starting from a 1 meter cube hole in the ground,
	//we dig up, down, left, or right the specified number of meters.
	//we also point the trench the RGB color 
	//at the end, how many cubic meters of lava can the lagoon hold
	//after digging out the interior

	//initialize a grid of D18tiles.


	std::cout << "Day 18:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}

