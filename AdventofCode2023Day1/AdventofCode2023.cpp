// AdventofCode2023Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "./headers/AdventofCode2023.h"

int main()
{
    std::cout << "Advent of code 2023 :)" << std::endl;
    concurrency::concurrent_vector<int> lines;
    concurrency::concurrent_vector<Day*> days;
    
    days.push_back( new Day1() );
    days.push_back( new Day2() );
    days.push_back( new Day3() );
    days.push_back( new Day4() );
    days.push_back( new Day5() );
    days.push_back( new Day5b() );
    days.push_back( new Day6() );
    days.push_back( new Day7() );
    days.push_back( new Day8() );
    days.push_back( new Day9() );
    days.push_back(new Day10());
    
    /*
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

    concurrency::concurrent_vector<std::pair<std::string, std::chrono::milliseconds>> durations;

    auto totalstart = std::chrono::high_resolution_clock::now();

        
    //running the days in parallel makes it slower T-T
    std::for_each(/*std::execution::par, */ days.begin(), days.end(), [&](Day* day) {  //[] is where the lambda function captures, by doing & it captures all local variables by reference.
        auto start = std::chrono::high_resolution_clock::now();

        //lines is a concurrent_vector<int>, it just counts the lines parsed from input file by the day.
        lines.push_back(day->day()); 

        auto finish = std::chrono::high_resolution_clock::now();

        //durations is a concurrent_vector<pairs<string,chrono::ms>>
        durations.push_back(std::make_pair(typeid(*day).name(), std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)));
        });
    //END PARALLEL LOOP

    auto totalfinish = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << "-------Times for each day in milliseconds -------" << std::endl;
    for (int i = 0; i < durations.size(); ++i) {
        std::cout << durations[i].first.substr(6) << ":\t" << durations[i].second.count() << "ms \t input size: " << lines[i] << " lines." << std::endl;
    }


    auto totalmilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(totalfinish - totalstart);
    std::cout << "all days total: " << totalmilliseconds.count() << "ms" << std::endl;

    system("pause");

}