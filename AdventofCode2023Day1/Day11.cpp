using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day11.h"



int Day11::day() {
	string line;
	fstream file("./inputs/day10input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 10:\t" << sum1 << "\tand " << sum2 << endl;
	return lines;
}