#pragma once
#include "./Day.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/*

https://adventofcode.com/2023/day/12
*/
class Day12 : public Day
{
private:

public:
	int day();
	
	bool picross(std::vector<int>* nums, std::string perm);
	std::string getNextPermutation(std::string line, std::vector<int>* optionals);
};

