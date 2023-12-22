#pragma once
#include "./Day.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/*

https://adventofcode.com/2023/day/12
*/
class Day12 : public Day
{
private:

public:
	int day();
	
	bool picross(std::vector<int>* holes, std::string* perm);
};

