#include "./headers/Day13.h"

int Day13::day() {
	std::string line;
	std::fstream file("./inputs/day13input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	std::vector<std::string> mirror;
	std::vector<std::vector<std::string>> mirrors;

	while (getline(file, line)) {
		lines++;
		std::stringstream ss(line);
		if (line.size()) {
			mirror.push_back(line);
		}
		else {
			mirrors.push_back(mirror);
			mirror.clear();
		}
	}
	mirrors.push_back(mirror); //get last one


	
	//part 1, 0 errors allowed in reflection
	std::vector<std::pair<int,int>> pairs; //need the pairs for part2
	for (int i = 0; i < mirrors.size(); ++i) {

		std::pair<int,int> a = std::make_pair(0, 0);

		a.first = findHori(&mirrors[i]);
		a.second = findVert(&mirrors[i]);

		pairs.push_back(a);
		sum1 += (a.first * 100) + a.second;
	}

	//part 2, 1 error is allowed in a reflection, also make sure it's not the same line as part 1
	for (int i = 0; i < mirrors.size(); i++) {
		sum2 += findHori(&mirrors[i], 1, pairs[i].first) * 100;
		sum2 += findVert(&mirrors[i], 1, pairs[i].second);
	}

	std::cout << "Day 13:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}

int Day13::findHori(std::vector<std::string>* mirror) {
	for (int i = 0; i < mirror->size() - 1; ++i) { //i is row, moving top to bottom

		int j = i;
		int k = i + 1;

		while (j >= 0 && k < mirror->size()) { //j and k are moving thru the rows

			if (mirror->at(j) != mirror->at(k)) {
				break;
			}
			j--; k++;
		}

		if (j == -1 || k == mirror->size()) { //horizontal reflection confirmed
			return i + 1;
		}
	}
	return 0;
}

int Day13::findHori(std::vector<std::string>* mirror, int tolerance, int prev) {

	for (int i = 0; i < mirror->size() - 1; ++i) { //i is row, moving top to bottom

		if (i+1 == prev) { continue; }

		int errors = 0;
		int j = i;
		int k = i + 1;

		while (j >= 0 && k < mirror->size()) { //j and k are moving thru the rows

			for (int m = 0; m < mirror->at(j).size(); ++m) { //count errors for each wrong character
				if (mirror->at(j)[m] != mirror->at(k)[m]) {
					if (++errors > tolerance) { break; }
				}
			}
			j--; k++;
		}
		if ((j == -1 || k == mirror->size()) && errors <= tolerance) { //horizontal reflection confirmed within tolerance
			return i + 1;
		}
	}
	return 0;
}

int Day13::findVert(std::vector<std::string>* mirror) {
	for (int l = 0; l < mirror->at(0).size() - 1; l++) {	//l is column, moving left to right
		int rowsReflected = 0;
		for (int i = 0; i < mirror->size(); i++) {			//i is row, moving top to bottom
			int j = l, k = l + 1;

			while (j >= 0 && k < mirror->at(i).size()) {	//j and k are moving thru i row to left and right
				if (mirror->at(i)[j] != mirror->at(i)[k]) {
					break;
				}
				j--; k++;
			}
			if (j == -1 || k == mirror->at(i).size()) {
				rowsReflected++;					//if they reached a side, this row is reflected on column l
			}
			else { break; }							//if a row breaks, no need to continue checking other rows. move on to next l.
		}
		if (rowsReflected == mirror->size()) {
			return l + 1;							//if number of reflected rows is same as rows in mirror, the columns are reflected at l
		}
	}
	return 0;
}


int Day13::findVert(std::vector<std::string>* mirror, int tolerance, int prev) {
	for (int l = 0; l < mirror->at(0).size() - 1; l++) {	//l is column, moving left to right
		if (l+1 == prev) { continue; }

		int errors = 0;
		int rowsReflected = 0;

		for (int i = 0; i < mirror->size(); i++) {			//i is row, moving top to bottom
			int j = l, k = l + 1;

			while (j >= 0 && k < mirror->at(i).size()) {	//j and k are moving thru i row to left and right
				if (mirror->at(i)[j] != mirror->at(i)[k]) {
					errors++;
				}
				j--; k++;
			}
			if (j == -1 || k == mirror->at(i).size() && errors <= tolerance) {		
				rowsReflected++;					//if they reached a side, this row is reflected on column l
			}
			else { break; }							//if a row breaks, no need to continue checking other rows. move on to next l.
		}											
		if (rowsReflected == mirror->size() && errors <= tolerance) {	
			return l+1;								//if number of reflected rows is same as rows in mirror, the columns are reflected at l within tolerance
		}
	}
	return 0;
}
