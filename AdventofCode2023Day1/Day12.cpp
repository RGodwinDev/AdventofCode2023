#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day12.h"



int Day12::day() {
	std::string line;
	std::fstream file("./inputs/day12input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 12:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}