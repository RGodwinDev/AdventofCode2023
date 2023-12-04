#include <iostream>
#include <fstream>
#include <string>
#include "./headers/Day4.h"
#include <vector>
#include <sstream>
#include <algorithm>
//#include <Windows.h> //if not on windows, comment this out

/* example card from input
Card   1: 30 48 49 69  1 86 94 68 12 85 | 86 57 89  8 81 85 82 68  1 22 90  2 74 12 30 45 69 92 62  4 94 48 47 64 49
		numbers left of '|' are winning numbers, right are playable numbers. count how many winning numbers are in playable numbers.
		the first match is worth 1 point, then further matches double your points. 2^(matches-1)
		add up how much all the cards are worth
*/

//Scratchcards
int Day4::day() {
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //THIS DOESNT WORK IF YOURE NOT ON WINDOWS, comment this and anything to do with hConsole out.

	std::string line;
	std::fstream file("./inputs/day4input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;
	std::vector<int> cardcopies(1, 1); //we have 1 copy of every card to start with, the original card.

	while (getline(file, line)) {
		lines++;

		//get the card number
		int card = stoi(line.substr(5, 4));
		sum2 += cardcopies[card - 1];

		//get positions for colon ':' and pole '|'
		int colpos = std::find(line.begin(), line.end(), ':') - line.begin();
		int polepos = std::find(line.begin(), line.end(), '|') - line.begin();


		//put left substring into left vector<int>
		std::string leftsub = line.substr(colpos+2, polepos - (colpos+3));
		std::vector<int> left;
		std::stringstream leftss(leftsub);
		std::string leftword;

		while (getline(leftss, leftword, ' ')) {
			if (leftword.size() > 0) { left.push_back(stoi(leftword)); }
		}
		std::sort(left.begin(), left.end()); //make left binary searchable O(leftlogleft)
		
		//put right substring into right vector<int>
		std::string rightsub = line.substr(polepos + 2, line.size() - polepos + 2);
		std::vector<int> right;
		std::stringstream rightss(rightsub);
		std::string rightword;

		while (getline(rightss, rightword, ' ')) {
			if (rightword.size() > 0) { right.push_back(stoi(rightword)); }
		}


		//check if each number in right is a winning number, matches == wins.
		int wins = 0;
		for (int num :right) { //O(rightlogleft) //old method was O(left * right)
			//bool won = false; //only used for the colors.
			if (binary_search(left.begin(), left.end(), num)) { 
				//won = true;
				wins++; 
			}

			/* fun with colors :), but it makes the program from under 30ms to 1500ms.
			if(won){
				//I had this set color to num value, but it looked bad. 
				//color can be anything between 0 and 255 and all nums were under 100.
				SetConsoleTextAttribute(hConsole, 10);				//COMMENT OUT if not windows
			}
			std::cout << num;
			SetConsoleTextAttribute(hConsole, 7);					//COMMENT OUT if not windows

			std::cout << " ";
			*/

		}
		//std::cout << std::endl;
		
		//points from wins on each card = 2^(wins-1)
		sum1 += (int)pow(2, wins - 1);

		//grow cardcopies vector if it needs more space.
		while (card + wins >= cardcopies.size()) {
			cardcopies.push_back(1);
		} //only issue is it'll give us copies of cards that dont exist.

		//the next (wins)amount of cards increase by the number of copies of the current card.
		while (--wins >= 0) {
			if (card + wins < cardcopies.size()) {
				cardcopies[card + wins] += cardcopies[card - 1];
			}
		}
	}

	std::cout << "Day 4:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}