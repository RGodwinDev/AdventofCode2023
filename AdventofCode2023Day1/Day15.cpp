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
	std::stringstream ss(input);
	std::string s;
	std::vector < std::map<std::string, int>> boxes(256); //part2 woo
	std::vector <std::string> orderqueue;
	while (getline(ss, s, ',')) {
		lines++; 
		sum1 += hash(s);
		auto equalsign = std::find(s.begin(), s.end(), '=');
		if (equalsign != s.end()) {
			std::string label = s.substr(0, equalsign - s.begin());
			int box = hash(label);
			int num = stoi(s.substr(equalsign - s.begin() + 1));
			boxes[box][label] = num;
			if (std::find(orderqueue.begin(), orderqueue.end(), label) == orderqueue.end()) {
				orderqueue.push_back(label);
			}
		}
		else { //operator is a -, remove the label from the box
			std::string label = s.substr(0, s.size() - 1);
			int box = hash(label);
			boxes[box].erase(label);
			int qitr = std::find(orderqueue.begin(), orderqueue.end(), label) - orderqueue.begin();
			if (qitr != orderqueue.size()) {
				orderqueue.erase(orderqueue.begin() + qitr);
			}
			
		}
	}

	std::vector<int> focuspowers(256, 0);
	std::vector<int> boxCount(256);
	for(int i = 0; i < orderqueue.size(); ++i){
		//second is the box number, first is label
		std::string label = orderqueue[i];
		int box = hash(label);
		if (boxes[box][label] > 0) {
			boxCount[box]++;
			long focuspower = box+1;
			focuspower *= boxCount[box];
			focuspower *= boxes[box][label];
			focuspowers[box] += focuspower;
		}
	}





	for (int i = 0; i < focuspowers.size(); ++i) {
		sum2 += focuspowers[i];
	}
	std::cout << "Day 15:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}


int Day15::hash(std::string s) {
	int current = 0;
	for (char c : s) {
		current += c - 0;
		current *= 17;
		current %= 256;
	}
	return current;
}

