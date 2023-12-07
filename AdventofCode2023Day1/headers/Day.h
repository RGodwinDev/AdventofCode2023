#pragma once
#include <mutex>

class Day
{
private:

public:
	virtual int day();
	std::mutex cout_mutex;
};

