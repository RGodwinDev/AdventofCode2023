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
//FLATTEN THE CONVERSIONS DOWN to 1 step.




int Day5::day() {
	std::string line;
	std::fstream file("./inputs/day5input.txt");
	int lines = 1;
	int sum2 = 0;

	//seed -> soil -> fertilizer -> water -> light -> temp -> humidity -> location
	std::vector<std::vector<__int64>> nums(8);

	//get seeds
	getline(file, line);
	std::stringstream ss(line.substr(7, (line.end() - line.begin()) - 7));
	std::string seedword;
	while (getline(ss, seedword, ' ')) {
		if (seedword.size() > 0) { nums[0].push_back(_strtoui64(&seedword[0], NULL, 10)); }
	}

	int step = 0;
	//get data and store it in nums[step]
	while (getline(file, line)) {
		lines++;
		if (line.size() == 0) { step++; getline(file, line); continue; } //skip this line and next line.
		std::stringstream linestream(line);
		std::string convert;
		while (getline(linestream, convert, ' ')) {
			if (convert.size() > 0) { nums[step].push_back(_strtoui64(&convert[0], NULL, 10)); }
		}
	}

	//all data is now in the nums vector	
	
	//dont worry about speed right now, sorting the vectors to allow binary search would be complicated.
	//TODO: sort

	for (int k = 0; k < nums[0].size(); ++k) { //for each seed
		for (int i = 1; i < nums.size(); ++i) {	//step thru the other vectors
			for (int j = 0; j < nums[i].size() - 2; j += 3) { //we're looking at sets of 3 numbers.

				//if a is between source && source + length-1
				//source is j+1
				//destination is j
				//range length is j+2
				//a = (a - source) + destination, a would always be >= to source, so negatives isnt a worry.
				__int64 a = nums[0][k];
				if (a >= nums[i][j + 1] && a <= nums[i][j + 1] + nums[i][j + 2] - 1) { //here is where we convert the numbers thru each filter					
					a = (a - nums[i][j + 1]) + nums[i][j];
					nums[0][k] = a;
					break;
				}
			}
			//if there wasnt a match, the seed stays the same. ez.
		}
	}
	__int64 lowest = INT64_MAX;
	for (__int64 seed : nums[0]) {
		lowest = std::min(lowest, seed);
	}





	std::cout << "Day 5:\t" << lowest << "\tand " << sum2 << std::endl;
	return lines;
}