#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day11.h"


/*

https://adventofcode.com/2023/day/11
*/
int Day11::day() {
	std::string line;
	std::fstream file("./inputs/day11input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 11:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}