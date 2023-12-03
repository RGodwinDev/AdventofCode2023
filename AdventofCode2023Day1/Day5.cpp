using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day5.h"



int Day5::day() {
	string line;
	fstream file("./inputs/day5input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	while (getline(file, line)) {
		lines++;


	}


	std::cout << "Day 5: " << sum1 << " and " << sum2 << endl;
	return lines;
}