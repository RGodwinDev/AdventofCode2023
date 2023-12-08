#pragma once
#include "./Day.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

//Camel Cards
class Day7 : public Day
{
private:

	//returns an int, 1->7 for which type of hand the card is, use for Part1
	static int getHandType1(std::vector<int>* hand);

	//returns an int, 1->7 for which type of hand the card is, use for Part2
	static int getHandType2(std::vector<int> *hand);

	//compares 2 hands of cards, requires 2 tuples of each: (handtype(int), cards(vector<int>) and value(int)).
	static bool customHandCompare(std::tuple<int, std::vector<int>, int>& handA, std::tuple<int, std::vector<int>, int>& handB);

public:
	int day();
};

