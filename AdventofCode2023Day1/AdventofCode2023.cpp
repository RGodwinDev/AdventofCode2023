// AdventofCode2023Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;
#include <chrono>
#include <iostream>
#include "./headers/Day1.h" // ./ starts at the project start, not where this file is in the project.
#include "./headers/Day2.h"
#include "./headers/Day3.h"
#include "./headers/Day4.h"
#include "./headers/Day5.h"
#include <vector>


int main()
{
    std::vector<int> lines;
    cout << "-------- results for each day --------" << endl;
    auto totalstart = std::chrono::high_resolution_clock::now();

    Day1 d1;
    lines.push_back(d1. v());
    auto onefinish = std::chrono::high_resolution_clock::now();
    Day2 d2;
    lines.push_back(d2.day());
    auto twofinish = std::chrono::high_resolution_clock::now();
    Day3 d3;
    lines.push_back(d3.day());
    auto threefinish = std::chrono::high_resolution_clock::now();
    Day4 d4;
    lines.push_back(d4.day());
    auto fourfinish = std::chrono::high_resolution_clock::now();
    Day5 d5;
    lines.push_back(d5.day());
    auto fivefinish = std::chrono::high_resolution_clock::now();

    auto totalfinish = std::chrono::high_resolution_clock::now();
    

    std::vector<std::chrono::milliseconds> durations;
    durations.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(onefinish - totalstart));
    durations.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(twofinish - onefinish));
    durations.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(threefinish - twofinish));
    durations.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(fourfinish - threefinish));
    durations.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(fivefinish - fourfinish));
     
   
    std::cout << endl;
    std::cout << "-------Times for each day in milliseconds -------" << endl;
    for (int i = 0; i < durations.size(); ++i) {
        std::cout << "day "<< (i+1) << ": " << durations[i].count() << "ms \t input size: " << lines[i] << " lines." << endl;
    }

    auto totalmilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(totalfinish - totalstart);
    std::cout << "all days in total: " << totalmilliseconds.count() << "ms" << endl;

}


