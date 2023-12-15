#pragma once
#include <vector>
#include "D15lense.h"
class D15box
{
private:
	std::vector<D15lense> lenses;
public:

	//default constructor, the box is empty
	D15box();

	//if the lense already exists, updates the focal length
	//if it doesnt exist, inserts it into the box.
	void insertOrUpdate(D15lense l);

	//removes a lense from the box by label
	void remove(std::string label);

	int getBoxPower();
};

