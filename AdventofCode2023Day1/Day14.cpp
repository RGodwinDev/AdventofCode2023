using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day14.h"



int Day14::day() {
	string line;
	fstream file("./inputs/day14input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 14:\t" << sum1 << "\tand " << sum2 << endl;
	return lines;
}