#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day15.h"


/*

https://adventofcode.com/2023/day/15
*/
int Day15::day() {
	std::string line;
	std::fstream file("./inputs/day15input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 15:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}