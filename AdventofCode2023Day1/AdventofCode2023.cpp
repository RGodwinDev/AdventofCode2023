// AdventofCode2023Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <chrono>
#include <iostream>
#include "./headers/Day.h"
#include "./headers/Day1.h" 
#include "./headers/Day2.h"
#include "./headers/Day3.h"
#include "./headers/Day4.h"
#include "./headers/Day5.h"
#include "./headers/Day6.h"
#include "./headers/Day7.h"
#include "./headers/Day8.h"
#include "./headers/Day9.h"
#include "./headers/Day10.h"
#include "./headers/Day11.h" 
#include "./headers/Day12.h"
#include "./headers/Day13.h"
#include "./headers/Day14.h"
#include "./headers/Day15.h"
#include "./headers/Day16.h"
#include "./headers/Day17.h"
#include "./headers/Day18.h"
#include "./headers/Day19.h"
#include "./headers/Day20.h"
#include "./headers/Day21.h" 
#include "./headers/Day22.h"
#include "./headers/Day23.h"
#include "./headers/Day24.h"
#include "./headers/Day25.h"

#include <vector>

int main()
{
    std::cout << "Advent of code 2023 :)" << std::endl;
    std::vector<int> lines;
    std::vector<Day*> days;
    
    days.push_back( new Day1() );
    days.push_back( new Day2() );
    days.push_back( new Day3() );
    days.push_back( new Day4() );
    days.push_back( new Day5() );
    days.push_back( new Day6() );
    /*
    days.push_back( new Day7() );
    days.push_back( new Day8() );
    days.push_back( new Day9() );
    days.push_back( new Day10() );
    days.push_back( new Day11() );
    days.push_back( new Day12() );
    days.push_back( new Day13() );
    days.push_back( new Day14() );
    days.push_back( new Day15() );
    days.push_back( new Day16() );
    days.push_back( new Day17() );
    days.push_back( new Day18() );
    days.push_back( new Day19() );
    days.push_back( new Day20() );
    days.push_back( new Day21() );
    days.push_back( new Day22() );
    days.push_back( new Day23() );
    days.push_back( new Day24() );
    days.push_back( new Day25() );
    */


    std::cout << "-------- results for each day --------" << std::endl;

    std::vector<std::chrono::milliseconds> durations;

    auto totalstart = std::chrono::high_resolution_clock::now();

    //loop thru the days and call their respective day().
    for (int i = 0; i < days.size(); ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        lines.push_back(days[i]->day());

        auto finish = std::chrono::high_resolution_clock::now();
        durations.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start));
    }

    auto totalfinish = std::chrono::high_resolution_clock::now();
     

   
    std::cout << std::endl << "-------Times for each day in milliseconds -------" << std::endl;
    for (int i = 0; i < durations.size(); ++i) {
        std::cout << "day "<< (i+1) << ":\t" << durations[i].count() << "ms \t input size: " << lines[i] << " lines." << std::endl;
    }

    
    auto totalmilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(totalfinish - totalstart);
    std::cout << "all days total: " << totalmilliseconds.count() << "ms" << std::endl;

    system("pause");
}
