#include "./headers/D19part.h"


D19part::D19part(std::vector<int> partValues) {
	this->x = partValues[0];
	this->m = partValues[1];
	this->a = partValues[2];
	this->s = partValues[3];
}

int D19part::getSumValues() {
	int sum = 0;
	sum += this->x;
	sum += this->m;
	sum += this->a;
	sum += this->s;
	return sum;
}