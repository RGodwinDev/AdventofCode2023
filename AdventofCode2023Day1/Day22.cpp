#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day22.h"


/*

https://adventofcode.com/2023/day/22
*/
int Day22::day() {
	std::string line;
	std::fstream file("./inputs/day22input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 22:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}