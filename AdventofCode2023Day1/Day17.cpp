#include "./headers/Day17.h"

int Day17::day() {
	std::string line;
	std::fstream file("./inputs/day17input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	std::vector<std::string> input;
	while (getline(file, line)) {
		lines++;
		input.push_back(line);
	}

	//move lava from the lava pool to the factory
	//minimize heat loss
	//while choosing a route that doesnt go straight for too long
	//each character is how much heat loss is incurred by entering it
	//the starting point is the top left
	//the end point is bottom right
	//move up to 3 blocks before we must turn
	//what is the least heat loss possible to incur

	//first thing that comes to mind is dijkstras




	std::cout << "Day 17:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}