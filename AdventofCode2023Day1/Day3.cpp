#include "./headers/Day3.h"

int Day3::day() {
	std::string line;
	std::fstream file("./inputs/day3input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	std::vector<std::string> rows;
	while (getline(file, line)) {
		lines++;
		rows.push_back(line);
	}
	file.close();

	//store positions of gears '*' as a pair, and ints adjacent to the gears in the vector.
	std::map<std::pair<int, int>, std::vector<int>> gears;


	//search for numbers in each row, when we find a number, check if its next to a symbol.
	for (int i = 0; i < rows.size(); ++i) {
		for (int j = 0; j < rows[i].size(); ++j) { //check each pos j in row i if it's a number
			if (isdigit(rows[i][j])) {
				
				//the number starting at pos j in row i
				int x = atoi(&rows[i][j]);
				int temp = x;
				int digits = 0;
				while (temp > 0) { digits++; temp /= 10; } //calc how many digits x has.

				bool nextToSymbol = isNextToSymbol(&gears, &rows, i, j, x, digits);
				
				//if x is next to a symbol, add x to sum1
				if (nextToSymbol) { sum1 += x; }
				//advance j by size of x, so we don't repeat it
				j += digits-1;

			}
		}
	}

	//add product of each gear to sum2
	//a gear needs 2+ values
	for (auto it = gears.begin(); it != gears.end(); it++) {
		if (it->second.size() > 1) {
			int y = 1;
			for (int n : it->second) { y *= n; }
			sum2 += y;
		}
	}

	std::cout << "Day 3:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}


bool Day3::isNextToSymbol(std::map<std::pair<int, int>, std::vector<int>>* gears, std::vector<std::string>* rows, int i, int j, int x, int digits) {

	//tracks if the number is next to a symbol.
	bool nextToSymbol = false;

	//check row above for a symbol
	if (i > 0) {
		std::string sub;
		//doesnt run into an edge
		if (j > 0 && j + digits + 1 < rows->at(i - 1).size()) { sub = rows->at(i - 1).substr(j - 1, digits + 2); }
		//hitting both edges? just use the whole row. //with the current data, this shouldnt be true.
		else if (j == 0 && j + digits + 1 >= rows->at(i - 1).size()) { std::cout << "row above hit both edges somehow" << std::endl;  sub = rows->at(i - 1); }
		//hitting just left edge
		else if (j + digits + 1 < rows->at(i - 1).size()) { sub = rows->at(i - 1).substr(j, digits + 1); }
		//hitting just right edge, go from j-1 -> end of row
		else if (j > 0){ sub = rows->at(i - 1).substr(j - 1, (rows->at(i-1).end() - rows->at(i-1).begin()) - j-1); }
		

		for (int k = 0; k < sub.size(); ++k) {
			if (!isdigit(sub[k]) && sub[k] != '.') {
				nextToSymbol = true;
				if (sub[k] == '*') {
					//if the number is on left edge
					if (j == 0) { gears->operator[]({ i - 1, j + k }).push_back(x); }
					else { gears->operator[]({ i - 1, j + k - 1 }).push_back(x); }
				} //we dont break here because it's possible a * comes after another symbol.
			}
		}
	}

	//check current row left side
	if (j > 0) { //num isnt on the left edge
		if (!isdigit(rows->at(i)[j - 1]) && rows->at(i)[j - 1] != '.') { //it's a symbol
			nextToSymbol = true;
			if (rows->at(i)[j - 1] == '*') { gears->operator[]({ i, j - 1 }).push_back(x); }
		}
	}

	//check current row right side
	if (j + digits < rows->at(i).size()) { //num isnt on the right edge
		if (!isdigit(rows->at(i)[j + digits]) && rows->at(i)[j + digits] != '.') { //it's a symbol
			nextToSymbol = true;
			if (rows->at(i)[j + digits] == '*') { gears->operator[]({ i, j + digits }).push_back(x); }
		}
	}

	//check row below
	if (i < rows->size() - 1) {
		std::string sub;
		//not hitting any edges
		if (j > 0 && j + digits < rows->at(i + 1).size()) { sub = rows->at(i + 1).substr(j - 1, digits + 2); }
		//hitting both edges, just use the whole row
		else if (j == 0 && j + digits >= rows->at(i + 1).size()) { std::cout << "row below hit both edges somehow" << std::endl;  sub = rows->at(i + 1); }
		//hitting just left edge
		else if (j + digits < rows->at(i + 1).size()) { sub = rows->at(i + 1).substr(j, digits + 1); }
		//hitting just right edge
		else if (j > 0) { sub = rows->at(i + 1).substr(j - 1, (rows->at(i + 1).end() - rows->at(i + 1).begin()) - j - 1); }

		for (int k = 0; k < sub.size(); ++k) {
			if (!isdigit(sub[k]) && sub[k] != '.') {
				nextToSymbol = true;
				if (sub[k] == '*') {
					//if on left edge
					if (j == 0) { gears->operator[]({ i + 1, j + k }).push_back(x); }
					else { gears->operator[]({ i + 1, j + k - 1 }).push_back(x); }
				}
			}
		}
	}

	return nextToSymbol;
}