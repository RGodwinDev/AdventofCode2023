#include "./headers/Day14.h"

int Day14::day() {
	std::string line;
	std::fstream file("./inputs/day14input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	std::vector<std::string> platform;
	while (getline(file, line)) {
		lines++;
		platform.push_back(line);
	}
	
	//part 1
	//to start with, tilt north
	tiltNorth(&platform);

	//count the rocks
	sum1 = countRocks(&platform);
	
	//part 1 finished, takes 1.5ms to tilt and count.
	

	//spinCycle(&platform);

	//part 2, we want to run a spin cycle, n w s e, 1 billion times... 
	//and return the countRocks value after the billionth time.
	//this is a detect cycle problem.
	//std::unordered_map<int, int> rockMap;
	//
	//for (int i = 0; i < 1000; ++i) { //at 10k this takes about 39 seconds. just 39 seconds * 100k...
		//spinCycle(&platform);
		//for (int i = 0; i < platform.size(); ++i) {
		//	std::cout << platform[i] << std::endl;
		//}
		//std::cout << std::endl;
	//}
	//sum2 = countRocks(&platform);


	std::cout << "Day 14:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}

int Day14::countRocks(std::vector<std::string>* platform) {
	size_t sum = 0;
	for (size_t i = 0; i < platform->size(); ++i) {
		for (size_t j = 0; j < platform->at(i).size(); ++j) {
			if (platform->at(i)[j] == 'O') {
				sum += platform->size() - i;
			}
		}
	}
	return sum;
}

//compare vs tiltSouth, is it actually faster?
//or was the while loop faster despite looking like it's slower
//while loop was definitely simpler tho.
void Day14::tiltNorth(std::vector<std::string>* platform) {
	std::vector<int> columnRockPlace(platform->at(0).size(), 0); //saves next empty spot for a rock to go
	for (int i = 0; i < platform->at(0).size(); ++i){
		if (platform->at(0)[i] != '.') {
			columnRockPlace[i] = 1;
		}
	}

	for (int i = 0; i < platform->at(0).size(); ++i){ //column i
		for (int j = 1; j < platform->size(); ++j) {  //row j
			if (j == columnRockPlace[i]) { //if the row is the place, skip it
				if (platform->at(j)[i] == 'O' || platform->at(j)[i] == '#') {
					columnRockPlace[i]++;
				}
				continue;
			}
			if (platform->at(j)[i] == 'O') {
				platform->at(columnRockPlace[i])[i] = 'O';
				platform->at(j)[i] = '.';
				while(columnRockPlace[i] < platform->size() && platform->at(columnRockPlace[i])[i] != '.'){
					columnRockPlace[i]++;
				}
				if (columnRockPlace[i] >= platform->size()) {
					break; //go to next column
				}
			}
			else if (platform->at(j)[i] == '#') {
				columnRockPlace[i] = j + 1;
			}
		}
	}
}

 
void Day14::tiltEast(std::vector<std::string>* platform) {
	//look at each row, from right to left
	std::vector<int> rowRockPlace(platform->size(), platform->at(0).size()-1); //saves next empty spot for a rock to go
	for (size_t i = 0; i < platform->size(); ++i) {
		if (platform->at(i)[platform->at(i).size()-1] != '.') {
			rowRockPlace[i] = platform->at(i).size()-2;
		}
	}

	for (size_t i = 0; i < platform->size(); ++i) {			//for each row top to bottom
		for (size_t j = platform->at(i).size() - 2; j >= 0; j--) {	//for each column right to left
			if (rowRockPlace[i] == j) {
				if(platform->at(i)[j] == 'O' || platform->at(i)[j] == '#') {
					rowRockPlace[i]--;
				}
				continue;
			}
			if (platform->at(i)[j] == 'O') {
				platform->at(i)[rowRockPlace[i]] = 'O';
				platform->at(i)[j] = '.';

				while (rowRockPlace[i] >= 0 && platform->at(i)[rowRockPlace[i]] != '.') {
					rowRockPlace[i]--;
				}

				if (rowRockPlace[i] <= 0) {
					break; //go to next row
				}
			}
			else if (platform->at(i)[j] == '#') {
				rowRockPlace[i] = j - 1;
			}
		}
	}
}
void Day14::tiltWest(std::vector<std::string>* platform) {
	for (int i = 1; i < platform->at(0).size(); ++i) {
		for (int j = 0; j < platform->size(); ++j) {
			if (platform->at(j)[i] == 'O') {
				//move west until it can't anymore
				int k = i;
				while (k > 0) {
					if (platform->at(j)[k - 1] != '.') {
						break;
					}
					k--;
				}
				platform->at(j)[i] = '.';
				platform->at(j)[k] = 'O';
			}
		}
	}
}

void Day14::tiltSouth(std::vector<std::string>* platform) {
	for (size_t i = platform->size() - 2; i >= 0; --i) {
		for (size_t j = 0; j < platform->at(i).size(); ++j) {
			if (platform->at(i)[j] == 'O') {
				//move it south until it cant anymore
				size_t k = i;
				while (k < platform->at(i).size()-1) {
					if (platform->at(k + 1)[j] != '.') {
						break;
					}
					k++;
				}
				platform->at(i)[j] = '.';
				platform->at(k)[j] = 'O';
			}
		}
	}
}
 
void Day14::spinCycle(std::vector<std::string>* platform) {
	tiltNorth(platform);
	tiltWest(platform);
	tiltSouth(platform);
	tiltEast(platform);
}