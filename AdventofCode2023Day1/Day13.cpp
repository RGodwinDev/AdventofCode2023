#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day13.h"



int Day13::day() {
	std::string line;
	std::fstream file("./inputs/day13input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 13:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}