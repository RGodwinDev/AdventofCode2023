#pragma once
#include "./Day.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "D19part.h"
#include <queue>

/*
Aplenty
https://adventofcode.com/2023/day/19
*/
class Day19 : public Day
{
private:

public:
    int day();

    int calcPart1(std::queue<std::pair<D19part, std::string>>* partqueue, 
        std::map<std::string, std::vector<std::tuple<char, char, int, std::string>>>* filters);
};

