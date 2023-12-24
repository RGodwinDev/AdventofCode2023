#include "./headers/D19partRanges.h"

D19partRanges::D19partRanges() {
	this->x.first = 1;
	this->m.first = 1;
	this->a.first = 1;
	this->s.first = 1;
	this->x.second = 4000;
	this->m.second = 4000;
	this->a.second = 4000;
	this->s.second = 4000;
}

uint64_t D19partRanges::calcRangesSize() {

	uint64_t size = this->x.second - (this->x.first-1);
	size *= this->m.second - (this->m.first-1);
	size *= this->a.second - (this->a.first-1);
	size *= this->s.second - (this->s.first-1);
	
	return size;
}