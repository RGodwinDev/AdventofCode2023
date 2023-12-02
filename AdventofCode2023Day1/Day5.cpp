using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day5.h"



int Day5::day() {
	string line;
	fstream file("./inputs/day5input.txt");
	int lines = 0;
	while (getline(file, line)) {
		lines++;
	}
	std::cout << "Day 5: " << "----" << " and " << "----" << endl;
	return lines;
}