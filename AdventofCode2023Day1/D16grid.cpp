#include "./headers/D16grid.h"


D16grid::D16grid(std::vector<std::string>* input) {
	this->energized = 0;
	for(int i = 0; i < input->size(); ++i){
		this->grid.push_back({});
		for (char c : input->at(i)) {
			this->grid[i].push_back(D16tile(c));
		}
	}
}

D16tile* D16grid::getTile(int a, int b) {
	return &this->grid[a][b];
}

int D16grid::countEnergized() { //O(n), this could be O(1) if we kept a count somehow
	return this->energized;
}

std::pair<int, int> D16grid::getGridSize() {
	return std::make_pair(this->grid.size(), this->grid[0].size());
}

std::vector<std::tuple<int, int, char>> D16grid::beam(std::tuple<int, int, char> beam) {
	//beam interaction logic goes here

	//beam is out of bounds, kill it by returning {}
	if (get<0>(beam) < 0 || 
		get<1>(beam) < 0 || 
		get<0>(beam) >= this->grid.size() || 
		get<1>(beam) >= this->grid[0].size()) {

		return {};
	}

	//get the tile and energize it.
	D16tile* tile = this->getTile(get<0>(beam), get<1>(beam));
	if (!tile->isEnergized()) {
		this->energized++;
	}
	tile->energize();
	
	//ask if tile has been hit from this direction before
	//if it has, kill the beam by returning {}
	
	if (tile->hasBeenHitFrom(get<2>(beam))) { return {}; }

	tile->addDirection(get<2>(beam));

	//now we see what type of tile we're dealing with.
	char type = tile->getType();


	// possible types . / \ - |

	/*
	*    .
	*	 beam just passes through, easy
	*/
	if (type == '.') {
		if (get<2>(beam) == 'N') {
			return { std::make_tuple(
				get<0>(beam) - 1,
				get<1>(beam),
				'N'
			) };
		}
		else if (get<2>(beam) == 'W') {
			return { std::make_tuple(
				get<0>(beam),
				get<1>(beam) - 1,
				'W'
			) };
		}
		else if (get<2>(beam) == 'S') {
			return { std::make_tuple(
				get<0>(beam) + 1,
				get<1>(beam),
				'S'
			) };
		}
		else { // East
			return { std::make_tuple(
				get<0>(beam),
				get<1>(beam) + 1,
				'E'
			) };
		}
	}

	/*
	*  / and \
	* beam gets reflected 90 degrees, depending on direction
	* 
	*/
	else if (type == '/') {
		if (get<2>(beam) == 'N') {
			return { std::make_tuple(
				get<0>(beam),
				get<1>(beam) + 1,
				'E'
			) };
		}
		else if (get<2>(beam) == 'W') {
			return { std::make_tuple(
				get<0>(beam) + 1,
				get<1>(beam),
				'S'
			) };
		}
		else if (get<2>(beam) == 'S') {
			return { std::make_tuple(
				get<0>(beam),
				get<1>(beam) - 1,
				'W'
			) };
		}
		else { // East
			return { std::make_tuple(
				get<0>(beam) - 1,
				get<1>(beam),
				'N'
			) };
		}
	}
	else if (type == char(92)) { // '\'
		if (get<2>(beam) == 'N') {
			return { std::make_tuple(
				get<0>(beam),
				get<1>(beam) - 1,
				'W'
			) };
		}
		else if (get<2>(beam) == 'W') {
			return { std::make_tuple(
				get<0>(beam) - 1,
				get<1>(beam),
				'N'
			) };
		}
		else if (get<2>(beam) == 'S') {
			return { std::make_tuple(
				get<0>(beam),
				get<1>(beam) + 1,
				'E'
			) };
		}
		else { // East
			return { std::make_tuple(
				get<0>(beam) + 1,
				get<1>(beam),
				'S'
			) };
		}
	}

	/*
	* splitters - and |
	* if it hits pointy side, beam continues on as if it's a '.'
	* if it hits flat side,
	* creates 2 beams
	* left/right for -
	* up/down for |
	*/
	else if (type == '-'){
		if (get<2>(beam) == 'W') { // continue on
			return { 
				std::make_tuple(
				get<0>(beam),
				get<1>(beam) - 1,
				'W')
			};
		}
		else if (get<2>(beam) == 'E') { //continue on
			return { std::make_tuple(
				get<0>(beam),
				get<1>(beam) + 1,
				'E'
			) };
		}
		else { //split into 2, left/right
			return {
				std::make_tuple(
					get<0>(beam),
					get<1>(beam) - 1,
					'W'),
				std::make_tuple(
					get<0>(beam),
					get<1>(beam) + 1,
					'E')
			};
		}
	}
	else if (type == '|'){
		if (get<2>(beam) == 'N') { //continue on
			return { std::make_tuple(
				get<0>(beam) - 1,
				get<1>(beam),
				'N'
			) };
		}
		else if (get<2>(beam) == 'S') { //continue on
			return { std::make_tuple(
				get<0>(beam) + 1,
				get<1>(beam),
				'S'
			) };
		}
		else { //split into 2, up/down
			return { 
				std::make_tuple(
					get<0>(beam) - 1,
					get<1>(beam),
					'N'),
				std::make_tuple(
					get<0>(beam) + 1,
					get<1>(beam),
					'S')
			};
		}
	}
	//invalid type, just destroy the beam? idk
	else {
		std::cout << "beam found an invalid tile" << std::endl;
		return {};
	}

}

void D16grid::deEnergize() {
	for (int i = 0; i < this->grid.size(); ++i) {
		for (int j = 0; j < this->grid[0].size(); ++j) {
			this->getTile(i, j)->deEnergize();
		}
	}
	this->energized = 0;
}
