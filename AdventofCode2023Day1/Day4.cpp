using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day4.h"
#include <vector>
#include <sstream>

/* example card from input
Card   1: 30 48 49 69  1 86 94 68 12 85 | 86 57 89  8 81 85 82 68  1 22 90  2 74 12 30 45 69 92 62  4 94 48 47 64 49
		numbers left of '|' are winning numbers, right are playable numbers. count how many winning numbers are in playable numbers.
		the first match is worth 1 point, then further matches double your points. 2^(matches-1)
		add up how much all the cards are worth
*/

int Day4::day() {
	string line;
	fstream file("./inputs/day4input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;
	vector<int> cardcopies(201, 1); //we have 1 copy of every card to start with, the original card.

	while (getline(file, line)) {
		lines++;

		//get the card number
		int card = stoi(line.substr(5, 4));

		//get the position of the colon ':'
		int colpos = std::find(line.begin(), line.end(), ':') - line.begin();
		//get the position of the pole '|'
		int polepos = std::find(line.begin(), line.end(), '|') - line.begin();


		//put left substring into left vector<int>
		string leftsub = line.substr(colpos+2, polepos - (colpos+3));
		vector<int> left;
		stringstream leftss(leftsub);
		string leftword;

		while (getline(leftss, leftword, ' ')) {
			if (leftword.size() > 0) { left.push_back(stoi(leftword)); }
		}

		
		//put right substring into right vector<int>
		string rightsub = line.substr(polepos + 2, line.size() - polepos + 2);
		vector<int> right;
		stringstream rightss(rightsub);
		string rightword;

		while (getline(rightss, rightword, ' ')) {
			if (rightword.size() > 0) { right.push_back(stoi(rightword)); }
		}


		//search right vector with left vector, matches == wins.
		int wins = 0;
		for (int i = 0; i < left.size(); ++i) {
			for (int j = 0; j < right.size(); ++j) {
				if (left[i] == right[j]) { wins++; }
			}
		}
		
		//points from wins on each card = 2^(wins-1)
		sum1 += (int)pow(2, wins - 1);


		//the next (wins)amount of cards increase by the number of copies of the current card.
		while (--wins >= 0) {
			if (card + wins < cardcopies.size()) {
				cardcopies[card + wins] += cardcopies[card - 1];
			}
		}
	}

	//add up all the copies of cards you have at the end.
	for (int i = 0; i < cardcopies.size(); ++i) {
		sum2 += cardcopies[i];
	}

	std::cout << "Day 4:\t" << sum1 << "\tand " << sum2 << endl;
	return lines;
}