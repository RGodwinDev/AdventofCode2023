#include "./headers/Day12.h"

int Day12::day() {
	std::string line;
	std::ifstream file("./inputs/day12input.txt");
	int lines = 0;
	

	std::vector<std::string> springPile;
	while (getline(file, line)) {
		lines++;
		springPile.push_back(line);
	}

	long long sum1 = 0, sum2 = 0; //just in case lol, dont want to come back after an hour and be overflowed

	for (std::string springRow : springPile) {
		std::vector<int> optionals;
		//std::vector<int> optionals2;
		std::vector<int> holeSizes;

		//split the row on " "
		int space = std::find(springRow.begin(), springRow.end(), ' ') - springRow.begin();

		//get the springs
		std::string springs = springRow.substr(0, space);
		for (int i = 0; i < springs.size(); ++i) {
			if (springs[i] == '?') { optionals.push_back(i); }
		}
		
		//get the numbers
		std::string nums = springRow.substr(space+1);
		std::stringstream getnums(nums);
		std::string t;
		while (getline(getnums, t, ',')) {
			holeSizes.push_back(stoi(t));
		}


		//std::string springsP2 = springs + '?' + springs + '?' + springs + '?' + springs + '?' + springs;
		//std::vector<int> holeSizes2;
		//for (int i = 0; i < holeSizes.size() * 5; ++i) {
		//	holeSizes2.push_back(holeSizes[i % holeSizes.size()]);
		//}		

		//for (int i = 0; i < springsP2.size(); ++i) {
		//	if (springsP2[i] == '?') { optionals2.push_back(i); }
		//}


		



		//Part 1
		//(2^n)-1 where n is number of optionals
		int limit = pow(2, optionals.size())-1;
		int j = limit;
		int shifts = 0;
		while (limit >>= 1) {
			shifts++;
		}
		int ways1 = 0;
		std::cout << springs << std::endl;
		while (j >= 0) {
			int bitcount = 0;
			int k = j;
			while (bitcount <= shifts) {
				if (k % 2 == 1) { springs[optionals[bitcount]] = '#'; }
				else { springs[optionals[bitcount]] = '.'; }
				k = k >> 1;
				bitcount++;
			}
			bool picrossed = picross(&holeSizes, &springs);
			if (picrossed) { ++ways1; }
			j--;
		}

		//part 1 takes about 45 seconds.
		//Part 2, basically copied part1, this will NOT pass in a reasonable timeframe 
		//unless I were to leave it on overnight at the very least, more likely several days.
		
		//int limit2 = pow(2, optionals2.size()) - 1;
		//int j2 = limit2;
		//int shifts2 = 0;
		//while (limit2 >>= 1) {
		//	shifts2++;
		//}
		//int ways2 = 0;
		//std::cout << springsP2 << std::endl;
		//while (j2 >= 0) {
		//	int bitcount2 = 0;
		//	int k2 = j2;
		//	while (bitcount2 <= shifts2) {
		//		if (k2 % 2 == 1) { springsP2[optionals2[bitcount2]] = '#'; }
		//		else { springsP2[optionals2[bitcount2]] = '.'; }
		//		k2 = k2 >> 1;  
		//		bitcount2++;
		//	}
		//	bool picrossed2 = picross(&holeSizes2, &springsP2);
		//	if (picrossed2) { ++ways2; }
		//	j--;
		//}

		sum1 += ways1;
		//sum2 += ways2;
		//std::cout << ways1 << ":" << sum1 << " " << ways2 << ":" << sum2 << std::endl;
	}




	std::cout << "Day 12:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}

//returns true if nums strictly fit the perm, no oversized holes
bool Day12::picross(std::vector<int>* holes, std::string* perm) {
	std::vector<int> permHoles;
	int hole = 0;
	for (int i = 0; i < perm->size(); ++i) {
		if (perm->at(i) == '#') { hole++; }
		else {
			if (hole > 0) {
				permHoles.push_back(hole);
			}
			hole = 0;
		}
	}
	if (hole > 0) { permHoles.push_back(hole); } //get the last hole if it ended on #


	if (holes->size() != permHoles.size()) { return false; }
	for (int i = 0; i < holes->size(); ++i) {
		if (holes->at(i) != permHoles[i]) {
			return false;
		}
	}
	return true;
}