#include "./headers/Day16.h"
#include <queue>


int Day16::day() {
	std::string line;
	std::fstream file("./inputs/day16input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;
	
	std::vector<std::string> input;
	while (getline(file, line)) {
		lines++;
		input.push_back(line);
	}

	D16grid copy = D16grid(&input); //copy that we don't modify, used for part 2.
	D16grid grid = copy; //part 1 grid


	// empty space .
	// mirrors / \
	//splitters | -
	
	//each tile on the grid converts some of the light to heat and melts rock in the cave
	//the beam enters top left, going left to right
	// if the beam hits a '.', it continues on
	// if the beam hits a mirror, / or \, the beam is reflected 90 degrees depending on the angle of the mirror
	// if the beam hits the point end of a splitter, | or -, the beam passes through as if it was empty space.
	// if the beam hits the flat side of a splitter, the beam splits into two beams, for |, up/down, for -, left and right
	// beams do not interact with other beams
	// a tile can have many beams passing through it at the same time.
	// A tile is engergized if that tile has at least one beam pass through it, reflect in it, or split in it.
	// how many tiles are energized at the end?

	std::queue<std::tuple<int, int, char>> beamqueue; //where each beam is currently + direction
	beamqueue.push(std::make_tuple(0, 0, 'E')); //original beam

	while (!beamqueue.empty()) {
		std::tuple<int, int, char> beam = beamqueue.front();
		beamqueue.pop();
		std::vector<std::tuple<int, int, char>> newBeams = grid.beam(beam);
		for (int i = 0; i < newBeams.size(); ++i) {
			beamqueue.push(newBeams[i]);
		}
	}

	sum1 = grid.countEnergized(); //counting is O(n), could make quicker by counting as we go somehow.
	
	//part 2, now do it again, but find the starting beam that energizes the MOST tiles
	//how many tiles does it energize.
	
	for (int i = 0; i < input.size(); ++i) { //get for all left/right beam starts
		//beams start from left, going east
		D16grid left = copy;
		
		
		std::queue<std::tuple<int, int, char>> leftbeamqueue;
		leftbeamqueue.push(std::make_tuple(i, 0, 'E'));

		while (!leftbeamqueue.empty()) {
			std::tuple<int, int, char> leftbeam = leftbeamqueue.front();
			leftbeamqueue.pop();
			std::vector<std::tuple<int, int, char>> newleftBeams = left.beam(leftbeam);
			for (int j = 0; j < newleftBeams.size(); ++j) {
				leftbeamqueue.push(newleftBeams[j]);
			}
		}


		//beams start from right, going west
		D16grid right = copy;

		std::queue<std::tuple<int, int, char>> rightbeamqueue;
		rightbeamqueue.push(std::make_tuple(i, input[0].size() - 1, 'W'));

		while (!rightbeamqueue.empty()) {
			std::tuple<int, int, char> rightbeam = rightbeamqueue.front();
			rightbeamqueue.pop();
			std::vector<std::tuple<int, int, char>> newrightBeams = right.beam(rightbeam);
			for (int j = 0; j < newrightBeams.size(); ++j) {
				rightbeamqueue.push(newrightBeams[j]);
			}
		}


		sum2 = std::max(left.countEnergized(), sum2);
		sum2 = std::max(right.countEnergized(), sum2);

	}

	for (int i = 0; i < input[0].size(); ++i) { //get for all up/down beam starts

		//beams start from the top, going south
		D16grid up = copy;
				
		std::queue<std::tuple<int, int, char>> upbeamqueue;
		upbeamqueue.push(std::make_tuple(0, i, 'S'));
		int count = 0;
		while (!upbeamqueue.empty()) {
			std::tuple<int, int, char> upbeam = upbeamqueue.front();
			upbeamqueue.pop();
			std::vector<std::tuple<int, int, char>> newupBeams = up.beam(upbeam);
			for (int j = 0; j < newupBeams.size(); ++j) {
				upbeamqueue.push(newupBeams[j]);
			}
		}


		//beams start from the bottom, going north
		D16grid down = copy;

		std::queue<std::tuple<int, int, char>> downbeamqueue;
		downbeamqueue.push(std::make_tuple(input.size()-1, i, 'N'));

		while (!downbeamqueue.empty()) {
			std::tuple<int, int, char> downbeam = downbeamqueue.front();
			downbeamqueue.pop();
			std::vector<std::tuple<int, int, char>> newdownBeams = down.beam(downbeam);
			for (int j = 0; j < newdownBeams.size(); ++j) {
				upbeamqueue.push(newdownBeams[j]);
			}
		}


		sum2 = std::max(up.countEnergized(), sum2);
		sum2 = std::max(down.countEnergized(), sum2);
	}

	
	std::cout << "Day 16:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}