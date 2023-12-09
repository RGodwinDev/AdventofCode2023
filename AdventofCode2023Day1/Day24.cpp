#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day24.h"


/*

https://adventofcode.com/2023/day/24
*/
int Day24::day() {
	std::string line;
	std::fstream file("./inputs/day24input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 24:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}