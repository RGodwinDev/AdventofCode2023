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

	for (int i = 0; i < filters.size(); ++i) {
		sort(filters[i].begin(), filters[i].end());
	}
	
	/*
	* END OF PARSING
	*/
	
	
	/*
	* PART 1 works flawlessly finishes in 5ms :)
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
	* PART 2 seems to work now. The real answer seems like it was actually just 0.
	* new approach, all changes go to newSeedRanges
	* replace old seedranges at the end
	* ONLY ranges that go OVER the filter get put back into seedranges to be processed
	* FIXED THE BUG WOW
	*/
	for (int i = 0; i < filters.size(); ++i) { //for each filter step
		std::vector<std::pair<__int64, __int64>> newSeedRanges;
		for (int j = 0; seedranges.size() > j; j++) { //check each seedrange
			
			__int64 seedstart = seedranges[j].first;
			__int64 seedrange = seedranges[j].second;
			bool filtered = false;
			//then we check if the seedrange hits a individual filter.
			for (int k = 0; k < filters[i].size(); ++k) { //each individual filter of a step
				__int64 destination = get<0>(filters[i][k]);
				__int64 source = get<1>(filters[i][k]);
				__int64 filterRange = get<2>(filters[i][k]);
				__int64 startdiff = seedstart - source; //if startdiff is negative, seedstart < source

				/*
				* FILTER IS FULLY INSIDE THE SEEDRANGE.
				*/
				if (seedstart < source && seedstart + seedrange > source + filterRange) {
					//seedstart is unaffected
					filtered = true;

					//new seedrange, end of filter -> end of original seedrange put back into original vector to check for more filters.
					__int64 afterFilterBegin = source + filterRange;
					__int64 afterFilterEnd = ((seedstart + seedrange) - (source + filterRange)) - 1;
					
					if (j == seedranges.size() - 1) { //at end of seedranges
						seedranges.push_back(std::make_pair(afterFilterBegin, afterFilterEnd));
					} 
					else { //otherwise insert
						seedranges.insert(seedranges.begin() + j + 1, std::make_pair(afterFilterBegin, afterFilterEnd));
					}

					//new seedrange, entire filter, put into newSeedRanges
					newSeedRanges.push_back(std::make_pair(destination, filterRange));
					newSeedRanges.push_back(std::make_pair(seedranges[j].first, abs(startdiff)));
					//seedrange should be moved to start of filter
					break;
				}

				/*
				* SEEDRANGE IS FULLY INSIDE FILTER
				*/
				else if (seedstart >= source && seedstart < source + filterRange 
					&& seedstart + seedrange > source && seedstart + seedrange <= source + filterRange) {

					filtered = true;
					//startdiff should be positive
					newSeedRanges.push_back(std::make_pair(destination + startdiff, seedrange));
					break;
				}

				/*
				* START IS INSIDE FILTER, END IS NOT
				*/
				else if(seedstart >= source && seedstart < source + filterRange){
					//add another seedrange, starting at end of filter to end of seedrange
					//adjust current seedrange to end of filter, and seedstart = destination + startdiff
					filtered = true;

					__int64 afterFilterBegin = source + filterRange;
					__int64 afterFilterEnd = ((seedstart + seedrange) - (source + filterRange)) - 1;
					if (j == seedranges.size() - 1) { //at end of seedranges
						seedranges.push_back(std::make_pair(afterFilterBegin, afterFilterEnd));
					}
					else { //otherwise insert
						seedranges.insert(seedranges.begin() + j + 1, std::make_pair(afterFilterBegin, afterFilterEnd));
					}

					newSeedRanges.push_back(std::make_pair(destination + startdiff, filterRange - startdiff));
					break;
				}

				/*
				* END IS INSIDE FILTER, START IS NOT
				*/
				else if (seedstart < source && seedstart + seedrange <= source + filterRange && seedstart + seedrange > source) {
					filtered = true;
					__int64 inFilterRange = seedrange - startdiff;
					
					newSeedRanges.push_back(std::make_pair(destination, inFilterRange));

					//start is before source, add range.first, and startdiff
					newSeedRanges.push_back(std::make_pair(seedranges[j].first, abs(startdiff)));
					break;
				}
			}
			/*
			* SEEDRANGE DID NOT GET FILTERED AT ALL
			*/
			if (!filtered) { newSeedRanges.push_back(seedranges[j]); }
		}
		std::pair<__int64,__int64> prevPair = std::make_pair(-1, -1);
		sort(newSeedRanges.begin(), newSeedRanges.end());
		seedranges = newSeedRanges;
		//dont need to check for dupes anymore :)
	}
	__int64 lowest1 = INT64_MAX, lowest2 = INT64_MAX;
	
	for (__int64 seed : seeds) { //faster to just search for lowest than sorting it.
		lowest1 = std::min(lowest1, seed);
	}
	lowest2 = seedranges[0].first != 0 ? seedranges[0].first : seedranges[1].first;

	std::cout << "Day 5:\t" << lowest1 << "\tand " << lowest2 << std::endl;
	return lines;
}