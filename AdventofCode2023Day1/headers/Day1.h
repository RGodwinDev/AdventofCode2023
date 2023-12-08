#pragma once
#include "./Day.h"
#include<fstream>
#include<string>
#include<iostream>

//Trebuchet?!
class Day1 : public Day
{
private:
	//checks if a substring in text, starting at pos i, is a number.
	static int checkWordNumber(std::string &text, int i);
public:
	//basically the main function of Day1
	int day();
};

