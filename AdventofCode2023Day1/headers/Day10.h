#pragma once
#include "./Day.h"
#include <vector>
#include <algorithm>


/*
Pipe Maze
https://adventofcode.com/2023/day/10
*/
class Day10 : public Day
{
private:

public:
	int day();
	int part1Traverse(std::pair<int, int> startPos, std::vector<std::string>* pipeMap, std::vector<std::pair<int,int>>* pipePositions);

	int part2Traverse(std::vector<std::string>* pipeMap, std::vector<std::pair<int, int>>* pipePositions, std::vector<std::pair<int, int>>* sortedPipePos);

	//searches for a pair<int,int> inside a sorted vector<pair<int,int>>
	//returns position, or -1 if not found.
	int pairBinarySearch(std::vector<std::pair<int, int>>* sortedPipePos, std::pair<int, int> key);
};

