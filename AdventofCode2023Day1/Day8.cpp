using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day8.h"



int Day8::day() {
	string line;
	fstream file("./inputs/day8input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 8:\t" << sum1 << "\tand " << sum2 << endl;
	return lines;
}