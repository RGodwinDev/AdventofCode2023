using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day6.h"



int Day6::day() {
	string line;
	fstream file("./inputs/day6input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 6:\t" << sum1 << "\tand " << sum2 << endl;
	return lines;
}