#include <iostream>
#include <string>
#include "./headers/Day6.h"
#include <vector>


int Day6::day() {
	std::string line;
	
	int sum1 = 1, sum2 = 0;

	/*
	* PART 1
	* just brute force these
	*/
	std::vector<int> time = { 42, 68, 69, 85 };
	std::vector<int> distance = { 284, 1005, 1122, 1341 };
	
	for (int i = 0; i < time.size(); ++i) {
		int count = 0;
		//brute force it lol
		for (int timeheld = 0; timeheld < time[i]; timeheld++) {
			if (timeheld * (time[i] - timeheld) > distance[i]) {
				count++;
			}
			else if(count > 0) { //past our winning range
				break;
			}
		}
		sum1 *= count;
		
	}
	
	/*
	* PART 2, jokes on you, there's not 4 races. It's just 1.
	*/
	long long time2 = 42686985; //42million
	long long distance2 = 284100511221341; //284 trillion
	//surely we can just brute force it again Kappa
	for (int timeheld = 0; timeheld < time2; timeheld++) {
		if (timeheld * (time2 - timeheld) > distance2) {
			sum2++;
		}
		else if (sum2 > 0) { //past our winning range, saves a little time but it's O(n/2) at best.
			break;
		}
	}
	//wait... that worked. BUT I know there is an O(1) approach out there.

	std::cout << "Day 6:\t" << sum1 << "\tand " << sum2 << std::endl;
	return 2;
}