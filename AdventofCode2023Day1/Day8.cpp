#include "./headers/Day8.h"



int Day8::day() {
	std::string line;
	std::fstream file("./inputs/day8input.txt");
	int lines = 0;
	long long sum1 = 0, sum2 = 0;


	/*
	* PARSING
	*/
	getline(file, line);
	std::string leftright = line;
	lines = 2;

	getline(file, line); //skip the blank line

	std::unordered_map<std::string, std::pair<std::string, std::string>> mappings;
	std::vector<std::string> endInA;

	//HQV = (LSD, NCQ) all lines follow this format
	while (getline(file, line)) {
		lines++;
		mappings[line.substr(0, 3)] = std::make_pair(line.substr(7, 3), line.substr(12, 3));
		if (line[2] == 'A') {
			endInA.push_back(line.substr(0, 3));
		}
	}
	file.close();
	/*
	* END PARSING
	*/



	/*
	* PART 1 LOOP
	*/
	int i = 0;
	std::string AAA = "AAA"; //start at AAA
	while (AAA != "ZZZ") {
		if (leftright[i%leftright.size()] == 'L') {
			AAA = mappings[AAA].first;
		}
		else {
			AAA = mappings[AAA].second;
		}
		i++;
	}
	sum1 = i;

	
	/*
	* PART 2 LOOP
	*/
	std::vector<int> stepsToZ;
	for (std::string place : endInA) {
		int j = 0;
		while (place[2] != 'Z') {
			//going left
			if (leftright[j % leftright.size()] == 'L') {
				place = mappings[place].first;
			}
			//going right
			else {
				place = mappings[place].second;
			}
			j++;			
		}
		stepsToZ.push_back(j);
	}


	//Calculate the Least Common Multiple of all the stepsToZ
	//LCM(a,b) = a*b/GCD(a,b)
	sum2 = 1;
	for (int steps: stepsToZ) {
		sum2 = std::lcm(steps, sum2);
	}


	std::cout << "Day 8:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}