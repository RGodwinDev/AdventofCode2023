#include <iostream>
#include "./headers/Day6.h"
#include <vector>

int Day6::day() {	
	int sum1 = 1, sum2 = 0;

	/*
	* PART 1
	* just brute force these
	* changed to descriminant of a quadratic trinomial.
	* sqrt(pow(time,2) - 4 * distance);
	*/
	std::vector<int> time = { 42, 68, 69, 85 };
	std::vector<int> distance = { 284, 1005, 1122, 1341 };
	
	for (int i = 0; i < time.size(); ++i) {

		//O(1) method
		int count = sqrt(pow(time[i], 2) - 4 * distance[i]);
		if (distance[i] % 2 == 1) { count++; }
		sum1 *= count;

		//bruteforce method
		//for (int timeheld = 0; timeheld < time[i]; timeheld++) {
		//	if (timeheld * (time[i] - timeheld) > distance[i]) {
		//		count++;
		//	}
		//	else if(count > 0) { //past our winning range
		//		break;
		//	}
		//}
	}
	
	/*
	* PART 2, jokes on you, there's not 4 races. It's just 1.
	*/
	long long time2 = 42686985; //42million
	long long distance2 = 284100511221341; //284 trillion

	//trying the O(1) way I found. descriminant of a quadratic trinomial.
	sum2 = sqrt(pow(time2, 2) - 4 * distance2);
	if (distance2 % 2 == 1) { sum2++; } //if distance is odd, add one.

	/*
	//surely we can just brute force it again Kappa
	for (int timeheld = 0; timeheld < time2; timeheld++) {
		if (timeheld * (time2 - timeheld) > distance2) {
			sum2++;
		}
		else if (sum2 > 0) { //past our winning range, saves a little time but it's O(n/2) at best.
			break;
		}
	}
	*/
	//wait... that worked. BUT I know there is an O(1) approach out there.


	std::cout << "Day 6:\t" << sum1 << "\tand " << sum2 << std::endl;
	return 2;
}