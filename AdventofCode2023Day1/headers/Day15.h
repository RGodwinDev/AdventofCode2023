#pragma once
#include "./Day.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <queue>
/*
Lens Library
https://adventofcode.com/2023/day/15
*/
class Day15 : public Day
{
private:

public:
	int day();

	//hashes the given string
	int hash(std::string s);
};

