#pragma once
#include "D15boxes.h"
#include "D15box.h"
#include "D15lense.h"
#include <vector>
#include <string>

class D15boxes
{
private:
	std::vector<D15box> boxes;

	//called from remove and insertOrUpdate
	int decideBox(std::string label);

public:
	//constructor
	D15boxes();

	//inserts or updates the given lense
	void insertOrUpdate(D15lense l);

	//removes the lense with the label
	void remove(std::string label);

	//calculates the total focal power of all the lenses inside all the boxes
	int calcFocalPower();

};

