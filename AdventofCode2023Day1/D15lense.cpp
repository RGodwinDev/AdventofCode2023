#include "./headers/D15lense.h"

D15lense::D15lense(std::string s)
{
	//if we're constructing a lense, s will be "label=focallength"
	auto equalsign = std::find(s.begin(), s.end(), '=');
	this->label = s.substr(0, equalsign - s.begin());
	this->focalLength = stoi(s.substr(equalsign - s.begin() + 1));
}

std::string D15lense::getLabel() {
	return this->label;
}

int D15lense::getFocalLength() {
	return this->focalLength;
}

void D15lense::setFocalLength(int l) {
	this->focalLength = l;
}