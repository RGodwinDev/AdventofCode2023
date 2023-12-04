// AdventofCode2023Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;
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

#include <vector>

int main()
{
    std::vector<int> lines;
    std::vector<Day*> days;
    
    days.push_back( new Day1() );
    days.push_back( new Day2() );
    days.push_back( new Day3() );
    days.push_back( new Day4() );
    days.push_back( new Day5() );
    days.push_back( new Day6() );
    days.push_back( new Day7() );
    days.push_back( new Day8() );
    days.push_back( new Day9() );
    days.push_back( new Day10() );



    cout << "-------- results for each day --------" << endl;

    std::vector<std::chrono::milliseconds> durations;

    auto totalstart = std::chrono::high_resolution_clock::now();

    //loop thru the days and time how long it takes to call each one.
    for (int i = 0; i < days.size(); ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        lines.push_back(days[i]->day());

        auto finish = std::chrono::high_resolution_clock::now();
        durations.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start));
    }

    auto totalfinish = std::chrono::high_resolution_clock::now();
     

   
    std::cout << endl << "-------Times for each day in milliseconds -------" << endl;
    for (int i = 0; i < durations.size(); ++i) {
        std::cout << "day "<< (i+1) << ": " << durations[i].count() << "ms \t input size: " << lines[i] << " lines." << endl;
    }

    
    auto totalmilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(totalfinish - totalstart);
    std::cout << "all days total: " << totalmilliseconds.count() << "ms" << endl;

    system("pause");
}
