#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day17.h"



int Day17::day() {
	std::string line;
	std::fstream file("./inputs/day17input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 17:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}