#include "./headers/D16tile.h"

D16tile::D16tile(char type) {
	this->type = type;
	this->energized = false;
}

char D16tile::getType() {
	return this->type;
}

void D16tile::energize() {
	this->energized = true;
}

bool D16tile::isEnergized() {
	return this->energized;
}

bool D16tile::hasBeenHitFrom(char c) {
	return std::find(this->directions.begin(), this->directions.end(), c) != this->directions.end();
}

void D16tile::addDirection(char c) {
	this->directions.push_back(c);
}
