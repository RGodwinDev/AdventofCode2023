#pragma once
#include <map>
#include <vector>
#include <string>
#include "./Day.h"
//Gear Ratios
class Day3 : public Day
{
private:
	/*
	helper function for day(). Checks for symbol around a number.
	If symbol is a '*', saves position of the '*' and number in gears.
	*/
	bool isNextToSymbol(map<pair<int, int>, vector<int>>* gears, vector<string>* rows, int i, int j, int x, int digits);

public:
	int day();
};

