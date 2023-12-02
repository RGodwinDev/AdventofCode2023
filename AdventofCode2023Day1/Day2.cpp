using namespace std;
#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include "./headers/Day2.h"

int Day2::day() {
	string line;
	fstream file("./inputs/day2input.txt");
	int ids = 0;
	int maxreds = 12, maxgreens = 13, maxblues = 14;
	int sum = 0;
	int lines = 0;
	while (getline(file, line)) {
		lines++;
		int reds = 0, greens = 0, blues = 0;
		int gameid = stoi(line.substr(4,4));
		//use 2 pointers, find :, then find ; over and over.
		int pos = find(line.begin(), line.end(), ':') - line.begin() + 1;
		int pos2 = find(line.begin() + pos, line.end(), ';') - line.begin() + 1;
		while (pos < line.size()-1) {
			if (pos2 >= line.size()){
				pos2 = line.size() - 1;
			}
			string hand = line.substr(pos+1, (pos2 - pos) - 1);
			//got individual handfulls now.
			
			stringstream ss(hand);
			string word;
			int wordcount = 0;
			int n = 0;
			while (ss >> word) {
				if (wordcount % 2 == 0) { //check for number
					n = stoi(word);
				}
				else { //check for color
					if (word[0] == 'r') { reds = max(reds, n); }
					else if (word[0] == 'g') { greens = max(greens, n); }
					else if (word[0] == 'b') { blues = max(blues, n); }
					n = 0;
				}
				wordcount++;
			}

			pos = pos2;
			pos2 = find(line.begin() + pos, line.end(), ';') - line.begin() + 1;
		}
		 
		if (reds <= maxreds && greens <= maxgreens && blues <= maxblues) {
			ids += gameid;
		}
		int product = reds * greens * blues;
		sum += product;
	}
	std::cout << "Day 2: " << ids << " and " << sum << endl;
	return lines;
}