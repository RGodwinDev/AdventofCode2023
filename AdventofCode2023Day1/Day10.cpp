#include "./headers/Day10.h"


int Day10::day() {
	std::string line;
	std::fstream file("./inputs/day10input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	std::vector<std::string> pipeMap;
	while (getline(file, line)) {
		lines++;
		pipeMap.push_back(line);
	}

	// | is north/south
	// - is east/west
	// L is north/east
	// J is north/west
	// 7 is south/west
	// F is south/east
	// . is ground, no pipes lead to it
	// S is starting position of animal

	//find S
	std::pair<int, int> startPos;
	for (int i = 0; i < pipeMap.size(); ++i) {
		auto place = std::find(pipeMap[i].begin(), pipeMap[i].end(), 'S');
		if (place != pipeMap[i].end()) {
			//found S
			startPos = std::make_pair(i, place - pipeMap[i].begin());
			break;
		}
	}

	//pipePositions is in traverse order
	std::vector<std::pair<int, int>> pipePositions;
	int stepsToFurthest = part1Traverse(startPos, &pipeMap, &pipePositions);

	//sortedPipePos is in sorted order for binary search
	std::vector<std::pair<int, int>> sortedPipePos = pipePositions;
	
	//note: sorting made the algo go from <10ms to in the 40-45ms range
	//# of pipe positions just barely under 13.3k, binary search = ceil(log2(13.3k)) -> 14 steps
	//we could give part1Traverse another vector, one for traverse order, and the other sorted order, sort upon insert.
	//might make part1 twice as long but should make total time significantly shorter.
	sort(sortedPipePos.begin(), sortedPipePos.end());

	int possibleNests = part2Traverse(&pipeMap, &pipePositions, &sortedPipePos);


	std::cout << "Day 10:\t" << stepsToFurthest << "\tand " << possibleNests << std::endl;
	return lines;
}


int Day10::part1Traverse(std::pair<int, int> startPos, 
	std::vector<std::string>* pipeMap, 
	std::vector<std::pair<int,int>>* pipePositions) {
	
	std::pair<int, int> curPos = std::make_pair(-1,-1);
	std::vector<char> east = { '-', 'J', '7' };
	std::vector<char> north = { '|', '7', 'F' };
	std::vector<char> west = { '-', 'L', 'F' };
	std::vector<char> south = { '|', 'L', 'J' };

	//first thing to do, check north east west south. 2 should be pipes connecting to S.
	pipePositions->push_back(startPos);
	/*
	* GET AN INITIAL DIRECTION
	*/
	if (startPos.first != 0) { //if i wasnt 0, north is available
		if (std::find(north.begin(), north.end(), 
			pipeMap->at(startPos.first-1)[startPos.second]) != north.end()) {

			curPos = std::make_pair(startPos.first - 1,startPos.second);
		}
	}
	else if(startPos.second != 0){ //if [i][j] j wasnt 0, west is available
		if (std::find(west.begin(), west.end(), 
			pipeMap->at(startPos.first)[startPos.second-1]) != west.end()) {

			curPos = std::make_pair(startPos.first, startPos.second - 1);
		}
	}
	else if (startPos.first != pipeMap->size() - 1) { //i isnt on the south edge of map
		if (std::find(south.begin(), south.end(), 
			pipeMap->at(startPos.first + 1)[startPos.second]) != south.end()) {

			curPos = std::make_pair(startPos.first + 1, startPos.second);
		}
	}
	else if (startPos.second != pipeMap->at(0).size() - 1) { //second isn't on east edge
		if (std::find(east.begin(), east.end(), 
			pipeMap->at(startPos.first)[startPos.second + 1]) != east.end()) {

			curPos = std::make_pair(startPos.first, startPos.second + 1);
		}
	}
	if (curPos.first == -1) { return 0; } //no pipes connected to animals start position



	/*
	* MAIN TRAVERSAL LOOP
	*/
	std::pair<int,int> prev = startPos;

	int stepsCount = 0;
	while (pipeMap->at(curPos.first)[curPos.second] != 'S') {
		stepsCount++;
		//what's the current pipe, and which direction are we going
		pipePositions->push_back(curPos);

		if (pipeMap->at(curPos.first)[curPos.second] == '|') {
			if (prev.first != curPos.first - 1) { //we're going north
				prev = curPos;
				curPos.first--;
			}
			else { //going south
				prev = curPos;
				curPos.first++;
			}
		}
		else if (pipeMap->at(curPos.first)[curPos.second] == '-') {
			if (prev.second != curPos.second - 1) { //we're going west
				prev = curPos;
				curPos.second--;
			}
			else { //going east
				prev = curPos;
				curPos.second++;
			}
		}
		else if (pipeMap->at(curPos.first)[curPos.second] == 'L') {
			if (prev.first != curPos.first - 1) { //we're going north
				prev = curPos;
				curPos.first--;
			}
			else { //going east
				prev = curPos;
				curPos.second++;
			}
		}
		else if (pipeMap->at(curPos.first)[curPos.second] == 'J') {
			if (prev.first != curPos.first - 1) { //we're going north
				prev = curPos;
				curPos.first--;
			}
			else { //going west
				prev = curPos;
				curPos.second--;
			}
		}
		else if (pipeMap->at(curPos.first)[curPos.second] == '7') {
			if (prev.first != curPos.first + 1) { //we're going south
				prev = curPos;
				curPos.first++;
			}
			else { //going west
				prev = curPos;
				curPos.second--;
			}
		}
		else if (pipeMap->at(curPos.first)[curPos.second] == 'F') {
			if (prev.first != curPos.first + 1) { //we're going south
				prev = curPos;
				curPos.first++;
			}
			else { //going east
				prev = curPos;
				curPos.second++;
			}
		}
	}
	/*
	* end of Traversal
	*/

	if (stepsCount % 2 == 1) {
		stepsCount += 1;
	}
	
	return stepsCount/2;
}


int Day10::part2Traverse(std::vector<std::string>* pipeMap, 
	std::vector<std::pair<int, int>>* pipePositions, 
	std::vector<std::pair<int, int>>* sortedPipePos) {
	//any tile that isnt part of the loop can possibly be enclosed.
	//find an edge of the maze
	//once we do, we can decide what side of the loop is in/out
	//we can search from the north edge, at the first position in the pipe.
	//this guarantees we will hit the pipe on the first pass.
	
	//possible forms the pipe will be on the first search: { -, 7, F, S }
	std::vector<char> possibleForms = { '-', '7', 'F', 'S' };

	
	std::pair<int, int> startPos = pipePositions->at(0);
	int posInPipe = -1;
	//first search from north edge towards startPos
	for (int i = 0; i < pipeMap->size(); ++i) {

		//if it looks like a pipe
		if (std::find(possibleForms.begin(), possibleForms.end(), 
			pipeMap->at(i)[startPos.second]) != possibleForms.end()) {

			//binary search the pipe to make sure it is part of the pipe.
			std::pair<int, int> curPos = std::make_pair(i, startPos.second);
			posInPipe = pairBinarySearch(sortedPipePos, curPos);

			if (posInPipe != -1) { break; } //found the pipe :)
		}
	}

	//we now have the position of a pipe piece posInPipe.
	//we start traversing the pipe
	//if the pipe is -, J, L, S and we are moving west
	//count positions below until we run into pipe again.
	//these are inside the pipe.
	//because it's a closed loop, it's impossible to run out to the edge.

	int inside = 0;

	//check the FIRST pipePositions(posInPipe)
	//the while loop doesn't catch it.
	std::pair<int, int> startPositions = pipePositions->at(posInPipe);
	if (pipeMap->at(startPositions.first)
		[startPositions.second] == '-' ||
		pipeMap->at(startPositions.first)
		[startPositions.second] == 'J' ||
		pipeMap->at(startPositions.first)
		[startPositions.second] == 'L' ||
		pipeMap->at(startPositions.first)
			[startPositions.second] == 'S') {

		for (int i = pipePositions->at(posInPipe).first + 1;
			i < pipeMap->size(); i++) {
			if (pairBinarySearch(sortedPipePos,
				std::make_pair(i, pipePositions->at(posInPipe).second)) == -1) {
				inside++;
			}
			else { break; } //piece of pipe found
		}
	}


	/*
	* MAIN TRAVERSAL
	*/
	//loop thru the rest of the pipe, 
	//only pipe forms we care about {-, J, L, S}
	//and ONLY if they are moving west.
	int curPos = (posInPipe + 1) % pipePositions->size();
	while (curPos != posInPipe) {

		//if - or L, if prev = east of cur, we moving west
		if (pipeMap->at(pipePositions->at(curPos).first)
			[pipePositions->at(curPos).second] == '-' ||
			pipeMap->at(pipePositions->at(curPos).first)
			[pipePositions->at(curPos).second] == 'L') {

			//get prev
			int prev = curPos - 1;
			if (prev == -1) { prev = pipePositions->size() - 1; }

			//check that prev was east of curPos
			if (pipePositions->at(prev).second - 1 == 
				pipePositions->at(curPos).second) {

				//we are moving west
				for (int i = pipePositions->at(curPos).first+1; 
					i < pipeMap->size(); i++) {
					if (pipeMap->at(i)[pipePositions->at(curPos).second] != '.') {

						//binary search pipe possible pipes, if -1 its not a piece of the pipe.
						if (pairBinarySearch(sortedPipePos,
							std::make_pair(i, pipePositions->at(curPos).second)) == -1) {
							inside++;
						}
						else { break; } //piece of pipe found
					}
					else { inside++; } //if it's a '.', count it.
				}
			}
		}
		//If J, if prev = north of cur, we moving west
		if (pipeMap->at(pipePositions->at(curPos).first)
			[pipePositions->at(curPos).second] == 'J') {

			//check that previousPos was north of curPos
			int prev = curPos - 1;
			if (prev == -1) { prev = pipePositions->size() - 1; }

			if (pipePositions->at(prev).first + 1 ==
				pipePositions->at(curPos).first) {

				//we are moving west
				for (int i = pipePositions->at(curPos).first + 1;
					i < pipeMap->size(); i++) {
					if (pipeMap->at(i)[pipePositions->at(curPos).second] != '.') {
						if (pairBinarySearch(sortedPipePos,
							std::make_pair(i, pipePositions->at(curPos).second)) == -1) {
							inside++;
						}
						else { break;  }
					}
					else { inside++; }
				}
			}
		}
		
		//BUG: S doesnt know what direction it is heading.
		//we need to get prev AND next to figure out what S looks like
		//and what direction it is heading.
		else if (pipeMap->at(pipePositions->at(curPos).first)
			[pipePositions->at(curPos).second] == 'S') {
			int prev = curPos - 1;
			if (prev == -1) { prev = pipePositions->size() - 1; }

			if (pipePositions->at(prev).second - 1 ==
				pipePositions->at(curPos).second) {

				//we are moving west :)
				for (int i = pipePositions->at(curPos).first+1;
					i < pipeMap->size(); i++) {
					if (pipeMap->at(i)[pipePositions->at(curPos).second] != '.') {
						int a = pairBinarySearch(sortedPipePos,
							std::make_pair(i, pipePositions->at(curPos).second));
						if (a == -1) { inside++; }
						else { break; } //piece of pipe found
					}
					else { inside++; }
				}
			}
		}
		curPos = (curPos + 1) % pipePositions->size();
	}
	/*
	* END of TRAVERSAL
	*/
	return inside;
}


int Day10::pairBinarySearch(
	std::vector<std::pair<int, int>>* sortedPipePos, 
	std::pair<int, int> key) {

	int l = 0, r = sortedPipePos->size() - 1;
	while (l <= r) {
		int m = l + ((r - l) / 2);
		if (sortedPipePos->at(m) == key) { return m; }
		if (sortedPipePos->at(m) > key) { r = m - 1; }
		else { l = m + 1; }
	}
	return -1;
}
