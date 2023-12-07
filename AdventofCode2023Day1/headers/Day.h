#pragma once
#include <iostream>
#include <mutex>

class Day
{
private:

public:
	virtual int day();
	static std::mutex cout_mutex;
};

