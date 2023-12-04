#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day20.h"



int Day20::day() {
	std::string line;
	std::fstream file("./inputs/day20input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 20:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}