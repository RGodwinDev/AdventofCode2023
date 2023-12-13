#include "./headers/Day12.h"

int Day12::day() {
	std::string line;
	std::ifstream file("./inputs/day12input.txt");
	int lines = 0;
	

	std::vector<std::string> springPile;
	while (getline(file, line)) {
		lines++;
		springPile.push_back(line);
	}

	int sum1 = 0, sum2 = 0;
	for (std::string springRow : springPile) {
		//original solution created all permutations of possible
		//strings that ? could be, . or #
		//it wouldve taken 40+ days at an hour per row. 
		//12 '?' = 12! = 479001600 permutations, for one line. theres 1000 lines.
		//putting this one off until i figure out a better strat.

	}




	std::cout << "Day 12:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}

//returns true if nums strictly fit the perm, no oversized holes
bool Day12::picross(std::vector<int>* nums, std::string perm) {
	return false;
}