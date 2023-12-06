#pragma once
#include "./Day.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

//Gear Ratios
class Day3 : public Day
{
private:
	/*
	helper function for day(). Checks for symbol around a number.
	If symbol is a '*', saves position of the '*' and number in gears.
	*/
	bool isNextToSymbol(std::map<std::pair<int, int>, std::vector<int>>* gears, std::vector<std::string>* rows, int i, int j, int x, int digits);

public:
	int day();
};

