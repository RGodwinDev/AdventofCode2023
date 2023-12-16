#pragma once
#include "D16tile.h"
#include <vector>
#include <iostream>

class D16grid
{
private:
	std::vector<std::vector<D16tile>> grid;
public:
	D16grid(std::vector<std::string>* input);
	//get the tile at the location [a][b]
	D16tile* getTile(int a,int b);

	//counts the number of energized tiles in the grid
	int countEnergized();

	//returns a vector of new beams, add them to the queue.
	std::vector<std::tuple<int,int,char>> beam(std::tuple<int, int, char> beam);
};

