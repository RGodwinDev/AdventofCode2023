#pragma once
#include <string>
#include <vector>

class D16tile
{
private:
	char type; // mirror, splitter, or empty
	bool energized;
	std::vector<char> directions;
public:
	//constructor
	D16tile(char type);
	
	//returns what kind of tile this is.
	char getType();

	//once energized, cant be unenergized.
	void energize();

	//true if the tile is energized
	bool isEnergized();

	
	bool hasBeenHitFrom(char c);

	//add a direction to directions
	void addDirection(char c);
};

