#pragma once
#include "./Day.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
/*
Parabolic Reflector Dish
https://adventofcode.com/2023/day/14
*/
class Day14 : public Day
{
private:

public:
	int day();
	int countRocks(std::vector<std::string>* platform);
	void tiltNorth(std::vector<std::string>* platform);
	void tiltSouth(std::vector<std::string>* platform);
	void tiltEast(std::vector<std::string>* platform);
	void tiltWest(std::vector<std::string>* platform);

	//spin cycle tilts north->west->south->east
	void spinCycle(std::vector<std::string>* platform);
};

