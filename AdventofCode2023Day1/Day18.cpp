#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day18.h"


/*

https://adventofcode.com/2023/day/18
*/
int Day18::day() {
	std::string line;
	std::fstream file("./inputs/day18input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 18:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}