#include "./headers/Day2.h"

int Day2::day() {

	std::string line;
	std::fstream file("./inputs/day2input.txt");

	int ids = 0, sum = 0;
	int maxreds = 12, maxgreens = 13, maxblues = 14;

	int lines = 0; //count the lines in the file, thats it.

	while (getline(file, line)) {
		lines++;

		int reds = 0, greens = 0, blues = 0;
		int gameid = stoi(line.substr(4,4)); //the gameid is always 4 into the line, and up to 4 in size.

		//use 2 pointers, find :, then find ; over and over.
		int pos = find(line.begin(), line.end(), ':') - line.begin() + 1;
		int pos2 = find(line.begin() + pos, line.end(), ';') - line.begin() + 1;

		while (pos < line.size()-1) {

			//last hand of a line doesnt have a ;, so go back one to stay in bounds.
			if (pos2 >= line.size()){ pos2 = line.size() - 1; } 

			//get a hand, put into stringstream
			std::stringstream ss(line.substr(pos+1, (pos2 - pos) - 1));

			std::string word;
			while (ss >> word) {
				int n = stoi(word); //first word is a number
				ss >> word;			//second word is a color
				if (word[0] == 'r') { reds = std::max(reds, n); }
				else if (word[0] == 'g') { greens = std::max(greens, n); }
				else if (word[0] == 'b') { blues = std::max(blues, n); }
			}

			//move positions to next.
			pos = pos2;
			pos2 = find(line.begin() + pos, line.end(), ';') - line.begin() + 1;
		}
		 
		//if the game had under the max possible for each color, it gets counted
		if (reds <= maxreds && greens <= maxgreens && blues <= maxblues) { ids += gameid; }
		//sum of powerset of all games.
		sum += reds * greens * blues;
	}

	std::lock_guard<std::mutex> guard(cout_mutex);
	std::cout << "Day 2:\t" << ids << " \tand " << sum << std::endl;
	return lines;
}