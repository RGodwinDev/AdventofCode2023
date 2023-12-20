#include "./headers/Day19.h"


int Day19::day() {
	std::string line;
	std::fstream file("./inputs/day19input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

										//part value, > or <, value compare, what to do if compare is true
	std::map<std::string, std::vector<std::tuple<char, char, int, std::string>>> filters;
	while (getline(file, line)) {
		lines++;
		if (line.size() == 0) { break; } //end of filters

		int left = std::find(line.begin(), line.end(), '{') - line.begin();
		int right = std::find(line.begin(), line.end(), ',') - line.begin();

		std::string filterName = line.substr(0, left);	

		//insert filter instructions into the map[filterName] vector
		while (right < line.size()) {
			char partVal = line[left+1];	
			char gl = line[left + 2];
			int compare = stoi(line.substr(left + 3));

			int colPos = std::find(line.begin() + left + 1, line.end(), ':') - line.begin() + 1;
			std::string result = line.substr(colPos, right - colPos);

			filters[filterName].push_back(std::make_tuple(partVal, gl, compare, result));

			left = right;
			right = std::find(line.begin()+right+1, line.end(), ',') - line.begin();
		}

		//get last instruction
		std::string result = line.substr(left + 1, line.size() - (left+2));
		filters[filterName].push_back(std::make_tuple('y', '=', 0, result));
	}

	//get the parts, and add them to partqueue
	std::queue<std::pair<D19part, std::string>> partqueue;
	while (getline(file, line)) {
		int commaPos = 0;
		std::vector<int> values;
		while (commaPos != line.size()) {
			values.push_back(stoi(line.substr(commaPos+3)));
			commaPos = std::find(line.begin()+commaPos+1, line.end(), ',') - line.begin();
		}
		partqueue.push(std::make_pair(D19part(values), "in")); //all parts start at the "in" filter
	}

	//now process the parts thru the filters, adding to accepted
	std::vector<D19part> accepted;

	while (!partqueue.empty()) {
		D19part p = partqueue.front().first;
		std::string filterName = partqueue.front().second;
		partqueue.pop();

		//put values of the part variables into a map
		//it shortens the next part significantly
		std::map<char, int> partVarMap;
		partVarMap['x'] = p.x;
		partVarMap['m'] = p.m;
		partVarMap['a'] = p.a;
		partVarMap['s'] = p.s;

		std::vector<std::tuple<char, char, int, std::string>> filter = filters[filterName];

		for(std::tuple<char, char, int, std::string> f : filter){
			if (get<1>(f) == '=') { //last instruction, just do it
				if (get<3>(f) == "A") {	accepted.push_back(p); }		//accepted, add to accepted vector.
				else if (get<3>(f) == "R") {}							//rejected, do nothing, rejected vector never got used.
				else { partqueue.push(std::make_pair(p, get<3>(f))); }	//put back into the partqueue with the filter name.
				break;
			}
			else if (get<1>(f) == '<') {
				if (partVarMap[get<0>(f)] < get<2>(f)){
					if (get<3>(f) == "A") {	accepted.push_back(p); }
					else if (get<3>(f) == "R") {}
					else { partqueue.push(std::make_pair(p, get<3>(f))); }
					break;
				}
			}
			else if (get<1>(f) == '>') {
				if (partVarMap[get<0>(f)] > get<2>(f)) {
					if (get<3>(f) == "A") {	accepted.push_back(p); }
					else if (get<3>(f) == "R") {}
					else { partqueue.push(std::make_pair(p, get<3>(f))); }
					break;
				}
			}
		}
	}
	for (D19part p : accepted) { sum1 += p.getSumValues(); }
	std::cout << "Day 19:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}