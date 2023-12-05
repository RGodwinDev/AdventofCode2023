#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day5.h"
#include <vector>
#include <sstream>
#include <algorithm>

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
								
				__int64 seed = seeds[k];
				if (seed >= source && seed <= source + range - 1) {				
					seed = (seed - source) + destination;
					seeds[k] = seed;
					break;
				}
			}
			//if there wasnt a match, the seed stays the same.
		}
	}

	/*
	* PART 2 also finishes super fast :)
	*/
	for (int i = 0; i < filters.size(); ++i) { //for each filter step
		std::vector<std::pair<__int64, __int64>> newSeedRanges;

		for (int j = 0; seedranges.size() > j; j++) { //check each seedrange
			__int64 seedstart = seedranges[j].first;
			__int64 seedrange = seedranges[j].second;

			//then we check if the seedrange hits a individual filter.
			for (int k = 0; k < filters[i].size(); ++k) { //each individual filter of a step
				__int64 destination = get<0>(filters[i][k]);
				__int64 source = get<1>(filters[i][k]);
				__int64 filterRange = get<2>(filters[i][k]);
				__int64 startdiff = seedstart - source; //if startdiff is negative, seedstart < source

				//filter is fully inside the seedrange.
				if (seedstart < source && seedstart + seedrange > source + filterRange) {
					//seedstart is unaffected
					
					//new seedrange, end of filter -> end of original seedrange put back into original vector to check for more filters.
					__int64 afterFilterBegin = source + filterRange+1;
					__int64 afterFilterEnd = (seedstart + seedrange) - (source + filterRange);
					
					if (j == seedranges.size() - 1) { //at end of seedranges
						seedranges.push_back(std::make_pair(afterFilterBegin, afterFilterEnd));
					} 
					else { //otherwise insert
						seedranges.insert(seedranges.begin() + j + 1, std::make_pair(afterFilterBegin, afterFilterEnd));
					}

					//new seedrange, entire filter, put into newSeedRanges
					newSeedRanges.push_back(std::make_pair(destination, filterRange));

					//seedrange should be moved to start of filter
					seedranges[j].second = abs(startdiff);
					break;
				}

				//start and end are inside filter, just adjust the start and move on :)
				else if (seedstart >= source && seedstart <= source + filterRange
					&& seedstart + seedrange >= source && seedstart + seedrange <= source + filterRange) {

					//startdiff should be positive
					seedranges[j].first = destination + startdiff;
					break;
				}
				//just start is inside filter, end isnt
				else if(seedstart >= source && seedstart <= source + filterRange){
					//add another seedrange, starting at end of filter to end of seedrange
					//adjust current seedrange to end of filter, and seedstart = destination + startdiff
					
					__int64 afterFilterStart = source + filterRange + 1;
					__int64 afterFilterRange = abs(seedrange - filterRange);
					seedranges.insert(seedranges.begin() + j + 1, std::make_pair(afterFilterStart, afterFilterRange));

					seedranges[j].first = destination + startdiff;
					seedranges[j].second = destination + filterRange - seedranges[j].first;
					break;
				}
				//just end is in filter, start isnt
				else if (seedstart + seedrange >= source && seedstart + seedrange <= source + filterRange) {
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
		seedranges = mergevec;
	}


	__int64 lowest1 = INT64_MAX, lowest2 = INT64_MAX;
	
	for (__int64 seed : seeds) {
		lowest1 = std::min(lowest1, seed);
	}
	
	lowest2 = seedranges[0].first;
	int i = 0;
	while (seedranges[i].first == 0) {
		i++;
	}
	lowest2 = seedranges[i].first;

	std::cout << "Day 5:\t" << lowest1 << "\tand " << lowest2 << std::endl;
	return lines;
}