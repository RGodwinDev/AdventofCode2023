#pragma once
#include "./Day.h"
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>


/*
Cosmic Expansion
https://adventofcode.com/2023/day/11
*/
class Day11 : public Day
{
private:

public:
	int day();

	//given 2 pairs, searches if they cross any empty columns or rows
	//returns number of empty columns and rows in pair<rows,columns>
	std::pair<int, int> emptySearch(std::pair<int, int> a, std::pair<int, int> b, std::vector<int>* emptyCol, std::vector<int>* emptyRow);

	//return the place of the first number greater than a
	int binarySearch(int a, std::vector<int>* empty);

	//return the place of the first number greater than a from the back
	int rbinarySearch(int a, std::vector<int>* empty);
};
