#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day10.h"


/*

https://adventofcode.com/2023/day/10
*/
int Day10::day() {
	std::string line;
	std::fstream file("./inputs/day10input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 10:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}