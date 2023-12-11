#pragma once
#include <iostream>
#include <mutex>
#include <chrono>

/*
https://adventofcode.com/2023
*/
class Day
{
private:

public:
	virtual int day();
	static std::mutex cout_mutex;
};

