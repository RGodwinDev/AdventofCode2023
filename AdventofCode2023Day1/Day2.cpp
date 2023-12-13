#include "./headers/Day2.h"

int Day2::day() {

	std::string in;
	std::ifstream file("./inputs/day2input.txt");


	int lines = 0; //counts the lines in the file, thats it.
	std::vector<std::string> input;
	while (getline(file, in)) {
		lines++;
		input.push_back(in);
	}
	file.close();

	//calculate the sum of good game ids, 
	//and the sum of the powerset of all hands
	int ids = 0, sum = 0;
	int maxreds = 12, maxgreens = 13, maxblues = 14;
	for(std::string line: input){
		int reds = 0, greens = 0, blues = 0;
		int gameid = stoi(line.substr(4,4));

		int pos = find(line.begin(), line.end(), ':') - line.begin() + 1;
		int pos2 = find(line.begin() + pos, line.end(), ';') - line.begin() + 1;

		while (pos < line.size()-1) {
			if (pos2 >= line.size()){ pos2 = line.size() - 1; }  

			std::stringstream ss(line.substr(pos+1, (pos2 - pos) - 1));

			std::string word;
			while (ss >> word) {
				int n = stoi(word); //first word is a number
				ss >> word;			//second word is a color
				if (word[0] == 'r') { reds = std::max(reds, n); }
				else if (word[0] == 'g') { greens = std::max(greens, n); }
				else if (word[0] == 'b') { blues = std::max(blues, n); }
			}

			pos = pos2;
			pos2 = find(line.begin() + pos, line.end(), ';') - line.begin() + 1;
		}
		 
		if (reds <= maxreds && greens <= maxgreens && blues <= maxblues) { ids += gameid; }
		sum += reds * greens * blues;
	}
	

	std::lock_guard<std::mutex> guard(cout_mutex);
	std::cout << "Day 2:\t" << ids << " \tand " << sum << std::endl;
	return lines;
}