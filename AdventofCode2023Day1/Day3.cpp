using namespace std;
#include <iostream>
#include <fstream>
#include "./headers/Day3.h"
#include <string>



int Day3::day() {
	string line;
	fstream file("./inputs/day3input.txt");
	int lines = 0;
	while (getline(file, line)) {
		lines++;
	}
	std::cout << "Day 3: " << "----" << " and " << "----" << endl;
	return lines;
}