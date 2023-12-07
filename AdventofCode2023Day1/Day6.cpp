#include "./headers/Day6.h"

int Day6::day() {	
	int sum1 = 1, sum2 = 0;
	std::string line;
	std::fstream file("./inputs/day6input.txt");
	int lines = 2;

	/*
	* PARSING BEGIN
	*/
	std::vector<int> time;
	getline(file, line);
	std::stringstream ss(line);
	std::string str;
	while (getline(ss, str, ' ')) {
		try {
			time.push_back(stoi(str));
		}
		catch (std::exception e) {

		}
	}
	ss.clear();
	std::vector<int> distance;
	getline(file, line);
	ss.str(line);
	while (getline(ss, str, ' ')) {
		try {
			distance.push_back(stoi(str));
		}
		catch (std::exception e) {

		}
	}

	/*
	* PARSING FINISHED
	*/


	/*
	* PART 1
	* just brute force these
	* changed to descriminant of a quadratic trinomial.
	* sqrt(pow(time,2) - 4 * distance);
	*/
	for (int i = 0; i < time.size(); ++i) {

		//O(1) method
		
		double d = sqrt((time[i] * time[i]) - (4 * distance[i]));
		int count = (floor((time[i] + d) / 2) - ceil((time[i] - d)/2)) + 1;
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

	//get time2 from the time vector
	long long time2 = 0; 
	int base = 0;
	for (int i = time.size()-1; i >= 0; i--) {
		//count the digits of each number as we get them
		
		time2 += time[i] * pow(10,base);
		long long x = time[i];
		while (x > 0) {
			base++;
			x /= 10;
		}
	}

	//get distance2 from distance vector
	base = 0;
	long long distance2 = 0;
	for (int i = distance.size() - 1; i >= 0; i--) {
		//count the digits of each number as we get them
		distance2 += distance[i] * pow(10, base);
		long long x = distance[i];
		while (x > 0) {
			base++;
			x /= 10;
		}
	}

	//trying the O(1) way I found. descriminant of a quadratic trinomial.
	double d = sqrt((time2 * time2) - (4 * distance2));
	sum2 = (floor((time2 + d) / 2) - ceil((time2 - d) / 2)) + 1;

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
	return lines;
}