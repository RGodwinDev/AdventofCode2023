#include "./headers/Day7.h"


int Day7::day() {
	std::string line;
	std::fstream file("./inputs/day7input.txt");
	int lines = 0;
	long long sum1 = 0, sum2 = 0;

	/*
	* PARSING WOO
	*/

	//each hand has a type, 5 cards, and a value
	std::vector<std::tuple<int, std::vector<int>, int>> hands1;
	std::vector<std::tuple<int, std::vector<int>, int>> hands2;

	while (getline(file, line)) {
		lines++;

		std::vector<int> hand1;
		std::vector<int> hand2;
		for (int i = 0; i < 5; ++i) {
			if (line[i] == 'A') { 
				hand1.push_back(14);
				hand2.push_back(14);
			}
			else if (line[i] == 'K') { 
				hand1.push_back(13);
				hand2.push_back(13);
			}
			else if (line[i] == 'Q') { 
				hand1.push_back(12);
				hand2.push_back(12);
			}
			else if (line[i] == 'J') { 
				hand1.push_back(11);
				hand2.push_back(1);
			}	
			else if (line[i] == 'T') { 
				hand1.push_back(10);
				hand2.push_back(10);
			}
			else { //its a number card
				int n = line[i] - '0';
				hand1.push_back(n);
				hand2.push_back(n);
			}
		}
		
		int value = stoi(line.substr(5, (line.end() - line.begin()) - 5));
		int type1 = getHandType1(&hand1);
		int type2 = getHandType2(&hand2);

		hands1.push_back(make_tuple(type1, hand1, value));
		hands2.push_back(make_tuple(type2, hand2, value));
	}

	/*
	* FINISHED PARSING WOO
	*/
	//DO NOT SORT THE INDIVIDUAL HANDS, IT MATTERS
	sort(hands1.begin(), hands1.end(), &Day7::customHandCompare);
	sort(hands2.begin(), hands2.end(), &Day7::customHandCompare);
	
	for (int i = 0; i < hands1.size(); ++i) {
		//value * position+1
		sum1 += (get<2>(hands1[i]) * (i + 1));
	}

	for (int i = 0; i < hands2.size(); ++i) {
		//value * position+1
		sum2 += (get<2>(hands2[i]) * (i + 1));
	}


	std::cout << "Day 7:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}


/*
* five of a kind - all 5 cards the same AAAAA
* four of a kind - 4 cards are the same AAAA8
* full house - 3 cards and 2 cards AAA88
* two pair - 2 sets of 2 cards AA884
* one pair - 1 set of 2 cards AA123
* high card - all the cards are distinct 12345
*/
int Day7::getHandType1(std::vector<int>* hand) {
	int type = 0;

	//get the frequency
	std::map<char, int> handFreq;
	for (int i = 0; i < hand->size(); i++) { handFreq[hand->at(i)]++; }

	//count the frequency
	std::vector<int> handCount(5, 0);
	for (auto it : handFreq) {
		handCount[it.second - 1]++;
	}

	int jokers = handFreq[1];

	//five of a kind
	if (handCount[4] == 1) { type = 7; }

	//four of a kind
	else if (handCount[3] == 1) { type = 6; }

	//Full house
	else if (handCount[2] == 1 && handCount[1] == 1) { type = 5; }

	//three of a kind
	else if (handCount[2] == 1) { type = 4; }

	//two pair
	else if (handCount[1] == 2) { type = 3; }

	//one pair
	else if (handCount[1] == 1) { type = 2; }

	//cards are all unique or all jokers
	else { type = 1; }

	return type;
}

int Day7::getHandType2(std::vector<int>* hand) {
	int type = 0;

	//get the frequency
	std::map<char, int> handFreq;
	for (int i = 0; i < hand->size(); i++) { handFreq[hand->at(i)]++; }

	//count the frequency
	std::vector<int> handCount(5,0);
	for (auto it : handFreq) { 
		if (it.first != 1) { //dont count the jokers
			handCount[it.second - 1]++;
		}
	}

	int jokers = handFreq[1];

	//five of a kind
	if(handCount[4] == 1){ type = 7; }

	//four of a kind
	else if (handCount[3] == 1) { type = 6; } 

	//Full house
	else if (handCount[2] == 1 && handCount[1] == 1) { type = 5; }

	//three of a kind
	else if (handCount[2] == 1) { type = 4; }

	//two pair
	else if (handCount[1] == 2) { type = 3; }

	//one pair
	else if (handCount[1] == 1) { type = 2; }

	//cards are all unique or all jokers
	else { type = 1; }

	/*
	* everything after here is for part2
	* for part1 change 'J' to 11 in the parsing.
	* no jokers == none of these will do anything.
	*/
	if (type == 1) {
		if (jokers == 1) { type = 2; }
		if (jokers == 2) { type = 4; }
		if (jokers == 3) { type = 6; }
		if (jokers >= 4) { type = 7; }
	}
	else if (type == 2) {
		if (jokers == 3) { type = 7; }
		if (jokers == 2) { type = 6; }
		if (jokers == 1) { type = 4; }
	}
	else if (type == 3) {
		if (jokers == 1) { type = 5; }
	}
	else if (type == 4) {
		if (jokers == 1) { type = 6; }
		if (jokers == 2) { type = 7; }
	}
	else if (type == 6) {
		if (jokers == 1) { type = 7; }
	}

	return type;
}

bool Day7::customHandCompare(std::tuple<int, std::vector<int>, int>& handA, std::tuple<int, std::vector<int>, int>& handB) {
	if (get<0>(handA) < get<0>(handB)) {
		return true;
	}
	else if (get<0>(handA) > get<0>(handB)) {
		return false;
	}
	//hand types are the same, check the card values
	int i = 0;
	
	while (i < 4 && get<1>(handA)[i] == get<1>(handB)[i] ) {
		i++; 
	}
	return get<1>(handA)[i] < get<1>(handB)[i];
}