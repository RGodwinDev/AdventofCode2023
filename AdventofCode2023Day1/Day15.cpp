#include "./headers/Day15.h"

int Day15::day() {
	std::string line;
	std::fstream file("./inputs/day15input.txt");
	int lines = 0;
	long long sum1 = 0, sum2 = 0;

	std::string input;
	while (getline(file, line)) {
		input = line;
	}

	D15boxes boxes = D15boxes();

	std::stringstream ss(input);
	std::string s;
	
	while (getline(ss, s, ',')) { //for each instruction...
		lines++; 
		sum1 += hash(s); //part 1 hash the whole instruction, add to sum, done.

		//part2, insert or remove the lense, per instruction = or -
		auto equalsign = std::find(s.begin(), s.end(), '=');
		if (equalsign != s.end()) {							// ==, insert/update lense
			D15lense a = D15lense(s);
			boxes.insertOrUpdate(a);
		}	
		else {												// -, remove the lense
			std::string label = s.substr(0, s.size() - 1);
			boxes.remove(label);			
		}

	}
	sum2 = boxes.calcFocalPower();

	std::cout << "Day 15:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}



//part 1 hash, part 2 uses the boxes.decideBox(label), which does the same thing.
int Day15::hash(std::string s) {
	int current = 0;
	for (char c : s) {
		current += c - 0;
		current *= 17;
		current %= 256;
	}
	return current;
}