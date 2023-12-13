#pragma once
#include "./Day.h"
#include <iostream>
#include <fstream>
#include <string>

/*
Point of Incidence
https://adventofcode.com/2023/day/13
*/
class Day13 : public Day
{
private:

public:
	int day();

	//checks a single mirror for a horizontal reflection within tolerance
	int findHori(std::vector<std::string>* mirror, int tolerance, int prev);
	//checks a single mirror for a horizontal reflection with no tolerance for error
	int findHori(std::vector<std::string>* mirror);

	//checks a single mirror for a vertical reflection within tolerance
	int findVert(std::vector<std::string>* mirror, int tolerance, int prev);
	//checks a single mirror for a vertical reflection with no tolerance for error
	int findVert(std::vector<std::string>* mirror);
};

