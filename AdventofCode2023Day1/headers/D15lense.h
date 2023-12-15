#pragma once
#include <vector>
#include <string>

class D15lense
{
private:
	std::string label;
	int focalLength;

public:
	D15lense(std::string s);

	std::string getLabel();
	int getFocalLength();
	void setFocalLength(int l);
};

