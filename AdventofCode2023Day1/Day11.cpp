#include "./headers/Day11.h"

int Day11::day() {
	std::string line;
	std::fstream file("./inputs/day11input.txt");
	int lines = 0;
	long long sum1 = 0, sum2 = 0;

	std::vector<std::string> cosmos;
	while (getline(file, line)) {
		lines++;
		cosmos.push_back(line);
	}
	file.close();
	//file read in done


	/*
	* Find Galaxy Locations and empty rows/columns
	*/
	std::vector<std::pair<int, int>> galaxyLocations; 

	std::vector<int> emptyRow; //vector because we dont go over a row more than once.
	std::set<int> notEmptyCol; //set because we only need to know it once, and are going over all the columns on each pass.

	//O(n*m), size of the cosmos
	for (int i = 0; i < cosmos.size(); i++) {
		int galCount = 0;
		for (int j = 0; j < cosmos[i].size(); j++) { //work rows first, then columns
			if (cosmos[i][j] == '#') {
				galCount++;
				galaxyLocations.push_back(std::make_pair(i, j)); //i is row, j is column
				notEmptyCol.insert(j); //column j is NOT empty
			}
		}
		if (galCount == 0) { emptyRow.push_back(i); }//row was empty
	}
	

	//generate an emptyCol vector using notEmptyCol vector.

	std::vector<int> emptyCol;
	auto notEmptyColIt = notEmptyCol.begin();
	for (int i = 0; i < cosmos.size(); ++i) {
		if (notEmptyColIt != notEmptyCol.end()) { //make sure iterator isnt over.

			if (i != *notEmptyColIt) { emptyCol.push_back(i); }
			else { notEmptyColIt++; }

		}
		else { emptyCol.push_back(i); } //if iterator is done, just put i into emptyCol.
	}

	/*
	* End finding Galaxy Locations 
	* and empty rows/columns
	*/

	/*
	* Calculate shortest distance between ALL galaxys.
	*/

	//shortest path between 2 galaxys = |y1 - y2| + |x1 - x2|works, but also need to add the warp distances
	//O((g^2 / 2) * (log x + log y)) where g is # of galaxys, x is number of emptyRows, y is number of emptyColumns
	for (int i = 0; i < galaxyLocations.size(); ++i) {
		std::pair<int, int> a = galaxyLocations[i];

		for (int j = i+1; j < galaxyLocations.size(); ++j) {

			
			std::pair<int, int> b = galaxyLocations[j];

			std::pair<int, int> y = emptySearch(a, b, &emptyCol, &emptyRow);

			sum1 += abs(a.first - b.first) + abs(a.second - b.second) + y.first + y.second;
			sum2 += abs(a.first - b.first) + abs(a.second - b.second) + (y.first * 999999) + (y.second * 999999);
			
		}
	}

	/*
	* END calculating distances
	*/

	std::cout << "Day 11:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}

std::pair<int, int> Day11::emptySearch(std::pair<int, int> a, std::pair<int, int> b, std::vector<int>* emptyCol, std::vector<int>* emptyRow) {
	
	//enforce that a is less than b
	//if (a.first > b.first) {
	//	int c = a.first;
	//	a.first = b.first;
	//	b.first = c;
	//}

	if (a.second > b.second) {
		int c = a.second;
		a.second = b.second;
		b.second = c;
	}

	//lower/upperbound are no goes for a sorted array.
	//went from 50ms to 500ms
	//returned to binary search and it's consistently <40ms
	int aRow = binarySearch(a.first, emptyRow);
	int bRow = rbinarySearch(b.first, emptyRow);
	int aCol = binarySearch(a.second, emptyCol);
	int bCol = rbinarySearch(b.second, emptyCol);

	//get the differences
	int rowDiff = bRow - aRow;
	int colDiff = bCol - aCol;
	
	return std::make_pair(rowDiff, colDiff);
}

int Day11::binarySearch(int a, std::vector<int>* empty) {
	int l = 0; int r = empty->size()-1;
	while (l <= r) {
		int m = l + ((r - l) / 2);
		if (empty->at(m) > a) {
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return r+1;
}

int Day11::rbinarySearch(int a, std::vector<int>* empty) {
	int l = 0; int r = empty->size()-1;
	while (l <= r) {
		int m = l + ((r - l) / 2);
		if (empty->at(m) >= a) {
			r = m-1;
		}
		else {
			l = m+1;
		}
	}
	return l;
}