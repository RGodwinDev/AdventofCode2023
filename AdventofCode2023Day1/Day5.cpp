#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day5.h"
#include <vector>
#include <sstream>
#include <algorithm>

//part 2, seeds row is different. 
// seeds is actually ##a ##b, ##a ##b, ##a ##b
// ##a is start of range of seeds
// ##b is size of the range

// the other ranges are still the same, store in a tuple
// (##dest, ##source, ##rangesize)

// for each range of seeds, we check if source is in range.
// if it is we convert the curseed into 1 2 or 3 new seed ranges


int Day5::day() {
	std::string line;
	std::fstream file("./inputs/day5input.txt");
	int lines = 1;
	

	/*
	* PARSING THE FILE AND STORING DATA
	*/
	//seed -> soil -> fertilizer -> water -> light -> temp -> humidity -> location
	std::vector<__int64> seeds; //part1 vec
	std::vector<std::pair<__int64, __int64>> seedranges; //part2 vec
	std::vector<std::vector<std::tuple<__int64, __int64, __int64>>> filters(7); //used in both p1 and p2


	//get seeds
	getline(file, line);
	std::stringstream ss(line.substr(7, (line.end() - line.begin()) - 7));
	std::string seedword;
	int oddseed = 0;
	while (getline(ss, seedword, ' ')) {
		if (seedword.size() > 0) { 
			seeds.push_back(_strtoui64(&seedword[0], NULL, 10));
			if (oddseed % 2 == 1) {
				seedranges.push_back(std::make_pair(seeds[oddseed-1], seeds[oddseed]));
			}
			oddseed++;
		}
	}
	sort(seeds.begin(), seeds.end());
	sort(seedranges.begin(), seedranges.end());
	
	
	int filterToFill = 0;
	getline(file, line); // skip the first blank line
	//get data and store it in nums[step]
	
	int lineCount = 0;
	while (getline(file, line)) {
		lines++;
		//blank line -> skip this line and next line.
		if (line.size() == 0) { filterToFill++; getline(file, line); continue; }
		std::stringstream linestream(line);
		std::string convert;
		__int64 filterNumA = 0;
		__int64 filterNumB = 0;
		__int64 filterNumC = 0;
		while (getline(linestream, convert, ' ')) {
			if (convert.size() > 0) { 
				filterNumA = filterNumB;
				filterNumB = filterNumC;
				filterNumC = _strtoui64(&convert[0], NULL, 10);
			}
		}
		filters[filterToFill].push_back(std::make_tuple(filterNumA, filterNumB, filterNumC));
	}
	//lets see if sorting filters affects part1
	for (int i = 0; i < filters.size(); ++i) {
		sort(filters[i].begin(), filters[i].end());
	}
	
	/*
	* END OF PARSING :)
	*/
	
	
	/*
	* PART 1 finishes in 5ms :)
	*/
	for (int k = 0; k < seeds.size(); ++k) { //for each seed
		for (int i = 0; i < filters.size(); ++i) {	//step thru the filters
			for (int j = 0; j < filters[i].size(); j++) { //we're looking at tuples
				__int64 destination = get<0>(filters[i][j]);
				__int64 source = get<1>(filters[i][j]);
				__int64 range = get<2>(filters[i][j]);
								
				__int64 a = seeds[k];
				if (a >= source && a <= source + range - 1) {				
					a = (a - source) + destination;
					seeds[k] = a;
					break;
				}
			}
			//if there wasnt a match, the seed stays the same. ez.
		}
	}

	/*
	* PART 2
	*
	*/
	for (int i = 0; i < filters.size(); ++i) { //for each filter step
		std::cout << "NEW FILTER " << i << std::endl;
		std::vector<std::pair<__int64, __int64>> newSeedRanges;
		std::cout << "seed ranges to filter: " << seedranges.size() << std::endl;
		for (int j = 0; seedranges.size() > j; j++) { //check each seedrange
			__int64 seedstart = seedranges[j].first;
			__int64 seedrange = seedranges[j].second;
			//then we check if the seedrange hits a filter somewhere.
			for (int k = 0; k < filters[i].size(); ++k) { //each individual filter of a step
				__int64 destination = get<0>(filters[i][k]);
				__int64 source = get<1>(filters[i][k]);
				__int64 filterRange = get<2>(filters[i][k]);
				__int64 startdiff = seedstart - source; //if startdiff is negative, seedstart < source

				//filter is fully inside the seedrange.
				if (seedstart < source && seedstart + seedrange > source + filterRange) {
					//std::cout << "filter fully inside, +2 ranges" << std::endl;
					//seedstart is unaffected
					//seedrange should be moved to start of filter
					
					//new seedrange, end of filter -> end of original seedrange put back into original vector to check for more filters.
					__int64 afterFilterBegin = source + filterRange+1;
					__int64 afterFilterEnd = (seedstart + seedrange) - (source + filterRange);
					
					if (j == seedranges.size() - 1) { //at end of seedranges
						seedranges.push_back(std::make_pair(afterFilterBegin, afterFilterEnd));
					} 
					else { //otherwise, insert
						seedranges.insert(seedranges.begin() + j + 1, std::make_pair(afterFilterBegin, afterFilterEnd));
					}

					//new seedrange, entire filter, put into newSeedRanges
					newSeedRanges.push_back(std::make_pair(destination, filterRange));

					seedranges[j].second = abs(startdiff);
					break;
				}

				//start and end are inside filter, just adjust the start and move on :)
				else if (seedstart >= source && seedstart <= source + filterRange
					&& seedstart + seedrange >= source && seedstart + seedrange <= source + filterRange) {
					//std::cout << "start and end inside, no additional ranges" << std::endl;

					//startdiff should be positive
					//seedstart = destination + startdiff;
					seedranges[j].first = destination + startdiff;
					break;
				}
				else if(seedstart >= source && seedstart <= source + filterRange){
					//std::cout << "just start is inside, +1 ranges" << std::endl;
					//just start is inside filter, end isnt
					//add another seedrange, starting at end of filter to end of seedrange
					//adjust current seedrange to end of filter, and seedstart = destination + startdiff
					
					__int64 afterFilterStart = source + filterRange + 1;
					__int64 afterFilterRange = abs(seedrange - filterRange);
					seedranges.insert(seedranges.begin() + j + 1, std::make_pair(afterFilterStart, afterFilterRange));


					seedranges[j].first = destination + startdiff;
					seedranges[j].second = destination + filterRange - seedranges[j].first;


					break;
				}
				else if (seedstart + seedrange >= source && seedstart + seedrange <= source + filterRange) {
					//std::cout << "just end is inside, +1 ranges" << std::endl;
					//just end is in filter
					//we need to calc a new start at start of filter and adjust the ranges
					//seedstart stays the same
					//startdiff = source - seedstart
					//new seedrange = startdiff
					
					//new in filter, start = source
					//range = seedrange - startdiff, ez
					__int64 inFilterStart = source;
					__int64 inFilterRange = seedrange - startdiff;
					newSeedRanges.push_back(std::make_pair(source, inFilterRange));
					seedranges[j].second = startdiff;


					break;
				}

			}
		}

		sort(seedranges.begin(), seedranges.end());
		sort(newSeedRanges.begin(), newSeedRanges.end());
		std::vector<std::pair<__int64, __int64>> mergevec;
		mergevec.reserve(seedranges.size() + newSeedRanges.size());
		merge(seedranges.begin(), seedranges.end(), newSeedRanges.begin(), newSeedRanges.end(), back_inserter(mergevec));
		seedranges = mergevec; //should be sorted :)
		
	}


	__int64 lowest1 = INT64_MAX, lowest2 = INT64_MAX;
	
	for (__int64 seed : seeds) {
		lowest1 = std::min(lowest1, seed);
	}
	//std::cout << "seedranges at the end: " << seedranges.size() << std::endl;
	lowest2 = seedranges[0].first;
	//for(int i = 0; i < seedranges.size(); ++i){
	//	std::cout << seedranges[i].first << std::endl;
	//}

	std::cout << "Day 5:\t" << lowest1 << "\tand " << lowest2 << std::endl;
	return lines;
}