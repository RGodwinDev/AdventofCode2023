#include "./headers/Day9.h"

int Day9::day() {
	std::string line;
	std::fstream file("./inputs/day9input.txt");
	int lines = 0;

	concurrency::concurrent_vector<concurrency::concurrent_vector<long>> readings;

	/*
	* PARSING
	*/
	while (getline(file, line)) {
		readings.push_back(*new concurrency::concurrent_vector<long>);
		std::string t;
		std::stringstream ss(line);
		while (getline(ss, t, ' ')) { readings[lines].push_back(stol(t)); }
		lines++;
	}
	file.close();
	/*
	* PARSING OVER
	*/

	/*
	* PART 1, GENERATE PREDICTED VALUES AND SUM THEM
	*/
	//should end up the same .size() as oasisReadings
	concurrency::concurrent_vector<int> predictedValues;
	concurrency::concurrent_vector<int> backPredictionValues;

	//this loop might be able to be parellelized.
	//edit: after testing LOL NO. Non Parallel is significantly faster
	//and uses a fraction of the cpu to do it.
	//I'll stop trying to parallel stuff until I learn about it from a book or something.
	//Running Day9 100x while parallel -> about 14.5 seconds
	//Running Day9 100x without parallel -> about 4.5 seconds
	std::for_each(/*std::execution::par,*/ readings.begin(), readings.end(),
		[&](concurrency::concurrent_vector<long> sitereading){
		std::vector<std::vector<int>> diffs(1);
		int numzeros = 0;

		//get first set of differences
		for (int j = 0; j < sitereading.size() - 1; j++) {
			diffs[0].push_back(sitereading[j + 1] - sitereading[j]);
			if (diffs[0][j] == 0) { numzeros++; }
		}

		//generate differences
		while (numzeros != diffs[diffs.size() - 1].size()) {
			diffs.push_back(std::vector<int>(diffs[diffs.size() - 1].size() - 1));
			for (int k = 0; k < diffs[diffs.size() - 2].size() - 1; ++k) {
				int d = diffs[diffs.size() - 2][k + 1] - diffs[diffs.size() - 2][k];
				diffs[diffs.size() - 1][k] = d;
				if (d == 0) { numzeros++; }
			}
			numzeros = 0;
		}

		int sum = 0;
		int sumback = 0;
		//predict the next number!
		for (int k = diffs.size() - 2; k >= 0; k--) {
			if (diffs[k].size() - 1 >= 0) { //skips 0 sized difference vectors
				sum += diffs[k][diffs[k].size() - 1];
				sumback = diffs[k][0] - sumback; //cant parallel because - isnt associative, the value of sumback would likely be wrong
			}
		}
		sum += sitereading[sitereading.size() - 1];
		predictedValues.push_back(sum);
		/*
		* PART 2, now predict the previous number!
		* wait, the prev loop does what I need it to
		*/
		sumback = sitereading[0] - sumback;
		backPredictionValues.push_back(sumback);
		});
	

	//while we can parallelize these, 
	//it doesnt actually seem to speed up or slow anything down, 
	//so I'll just leave it as is.
	long sum1 = std::reduce(std::execution::par, predictedValues.begin(), predictedValues.end(), 0);
	long sum2 = std::reduce(std::execution::par, backPredictionValues.begin(), backPredictionValues.end(), 0);

	std::cout << "Day 9:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}