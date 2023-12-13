#pragma once
#include "./Day.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <WinUser.h>


/*
Pipe Maze
https://adventofcode.com/2023/day/10
*/
class Day10b : public Day
{
private:

public:


	int day();



	//counts how many steps to get to the farthest point in the pipe from S.
	//writes down the pipe positions in the given pipePositions.
	int part1Traverse(std::pair<int, int> startPos,
		std::vector<std::string>* pipeMap,
		std::vector<std::pair<int, int>>* pipePositions,
		HWND console_handle);



	//counts how many nodes are enclosed by the loop.
	//requires the loop in traverse order, and sorted order, and the map.
	//might want a pipeMap class with the traverse methods in it.
	int part2Traverse(std::vector<std::string>* pipeMap,
		std::vector<std::pair<int, int>>* pipePositions,
		std::vector<std::pair<int, int>>* sortedPipePos,
		HWND console_handle);



	//searches for a pair<int,int> inside a sorted vector<pair<int,int>>
	//returns position, or -1 if not found.
	int pairBinarySearch(std::vector<std::pair<int, int>>* sortedPipePos,
		std::pair<int, int> key, HWND console_handle);

	void drawPair(std::pair<int, int> loc, std::pair<int, int> prev, std::tuple<int,int,int> color, HWND console_handle);

};

