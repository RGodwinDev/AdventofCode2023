#include "./headers/Day9.h"

int Day9::day() {
	std::string line;
	std::fstream file("./inputs/day9input.txt");
	int lines = 0;

	std::vector<std::vector<long>> readings;

	/*
	* PARSING
	*/
	while (getline(file, line)) {
		
		readings.push_back({});
		std::string t;
		std::stringstream ss(line);
		while (getline(ss, t, ' ')) {
			readings[lines].push_back(stol(t));
		}
		lines++;
	}
	/*
	* PARSING OVER
	*/

	/*
	* PART 1, GENERATE PREDICTED VALUES AND SUM THEM
	*/
	//should end up the same .size() as oasisReadings
	std::vector<int> predictedValues;
	std::vector<int> backPredictionValues;
	for (int i = 0; i < readings.size(); i++) {
		std::vector<std::vector<int>> diffs(1);
		int numzeros = 0;

		//get first vec of differences
		for (int j = 0; j < readings[i].size() - 1; j++) {
			diffs[0].push_back(readings[i][j + 1] - readings[i][j]);
			if (diffs[0][j] == 0) { numzeros++; }
		}

		//generate differences
		while (numzeros != diffs[diffs.size() - 1].size()) {
			diffs.push_back({});
			for (int k = 0; k < diffs[diffs.size() - 2].size() - 1; ++k) {
				int d = diffs[diffs.size() - 2][k + 1] - diffs[diffs.size() - 2][k];
				diffs[diffs.size() - 1].push_back(d);
				if (d == 0){ numzeros++; }
			}
			numzeros = 0;
		}

		int sum = 0;
		int sumback = 0;
		//predict the next number!
		for (int k = diffs.size()-2; k >= 0; k--) {
			if (diffs[k].size() - 1 >= 0) { //skips 0 sized difference vectors
				sum += diffs[k][diffs[k].size() - 1];
				sumback = diffs[k][0] - sumback;
			}
		}
		sum += readings[i][readings[i].size() - 1];
		predictedValues.push_back(sum);
		/*
		* PART 2, now predict the previous number!
		* wait, the prev loop does what I need it to /shrug
		*/
		sumback = readings[i][0] - sumback;
		backPredictionValues.push_back(sumback);
	}
	

	long sum1 = std::accumulate(predictedValues.begin(), predictedValues.end(), 0);
	long sum2 = std::accumulate(backPredictionValues.begin(), backPredictionValues.end(), 0);

	std::cout << "Day 9:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}