using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day7.h"



int Day7::day() {
	string line;
	fstream file("./inputs/day7input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 7:\t" << sum1 << "\tand " << sum2 << endl;
	return lines;
}