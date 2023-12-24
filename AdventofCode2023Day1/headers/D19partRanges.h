#pragma once
#include <utility>

class D19partRanges
{
private:
public:
	D19partRanges();

	uint64_t calcRangesSize();

	//i'd want these to be private but it'd turn into getter/setter central
	std::pair<int,int> x;
	std::pair<int,int> m;
	std::pair<int,int> a;
	std::pair<int,int> s;
};

