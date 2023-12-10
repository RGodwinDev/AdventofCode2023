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

	//counts how many steps to get to the farthest point in the pipe from S.
	//writes down the pipe positions in the given pipePositions.
	int part1Traverse(std::pair<int, int> startPos, std::vector<std::string>* pipeMap, std::vector<std::pair<int,int>>* pipePositions);

	//counts how many nodes are enclosed by the loop.
	//requires the loop in traverse order, and sorted order, and the map.
	//might want a pipeMap class with the traverse methods in it.
	int part2Traverse(std::vector<std::string>* pipeMap, std::vector<std::pair<int, int>>* pipePositions, std::vector<std::pair<int, int>>* sortedPipePos);

	//searches for a pair<int,int> inside a sorted vector<pair<int,int>>
	//returns position, or -1 if not found.
	int pairBinarySearch(std::vector<std::pair<int, int>>* sortedPipePos, std::pair<int, int> key);
};

