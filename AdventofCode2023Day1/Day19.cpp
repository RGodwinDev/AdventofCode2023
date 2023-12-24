#include "./headers/Day19.h"


int Day19::day() {
	std::string line;
	std::fstream file("./inputs/day19input.txt");
	int lines = 0;
	
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

	int sum1 = calcPart1(&partqueue, &filters);
	uint64_t sum2 = calcPart2(&filters);
	
	std::cout << "Day 19:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}



int Day19::calcPart1(std::queue<std::pair<D19part, std::string>>* partqueue, std::map<std::string, std::vector<std::tuple<char, char, int, std::string>>>* filters) {
	std::vector<D19part> accepted;

	while (!partqueue->empty()) {
		D19part p = partqueue->front().first;
		std::string filterName = partqueue->front().second;
		partqueue->pop();

		//put values of the part variables into a map
		//it shortens the next part significantly
		std::map<char, int> partVarMap;
		partVarMap['x'] = p.x;
		partVarMap['m'] = p.m;
		partVarMap['a'] = p.a;
		partVarMap['s'] = p.s;

		std::vector<std::tuple<char, char, int, std::string>> filter = filters->at(filterName);

		for (std::tuple<char, char, int, std::string> f : filter) {
			if (get<1>(f) == '=') { //last instruction, just do it
				if (get<3>(f) == "A") { accepted.push_back(p); }		//accepted, add to accepted vector.
				else if (get<3>(f) == "R") {}							//rejected, do nothing, rejected vector never got used.
				else { partqueue->push(std::make_pair(p, get<3>(f))); }	//put back into the partqueue with the filter name.
				break;
			}
			else if (get<1>(f) == '<') {
				if (partVarMap[get<0>(f)] < get<2>(f)) {
					if (get<3>(f) == "A") { accepted.push_back(p); }
					else if (get<3>(f) == "R") {}
					else { partqueue->push(std::make_pair(p, get<3>(f))); }
					break;
				}
			}
			else if (get<1>(f) == '>') {
				if (partVarMap[get<0>(f)] > get<2>(f)) {
					if (get<3>(f) == "A") { accepted.push_back(p); }
					else if (get<3>(f) == "R") {}
					else { partqueue->push(std::make_pair(p, get<3>(f))); }
					break;
				}
			}
		}
	}
	int sum = 0;
	for (D19part p : accepted) { sum += p.getSumValues(); }
	return sum;
}

uint64_t Day19::calcPart2(std::map<std::string, std::vector<std::tuple<char, char, int, std::string>>>* filters) {

	std::queue<std::pair<D19partRanges, std::string>> rangeQueue;
	rangeQueue.push(std::make_pair(D19partRanges(), "in")); //initial ranges, all x,m,a,s 1-4000

	uint64_t sum = 0;
	while (!rangeQueue.empty()) {
		D19partRanges r = rangeQueue.front().first;
		std::string filterName = rangeQueue.front().second;
		rangeQueue.pop();

		/*	//if theres a way to call variables from an object
			//without knowing what and how many there are
			//thatd make the map unneeded
		std::map<char, std::pair<int,int>> partRangeVarMap;
		
		partRangeVarMap['x'] = r.x;
		partRangeVarMap['m'] = r.m;
		partRangeVarMap['a'] = r.a;
		partRangeVarMap['s'] = r.s;
		*/


		//get the filter with filterName
		std::vector<std::tuple<char, char, int, std::string>> filter = filters->at(filterName);

		//run thru the filter
		for (std::tuple<char, char, int, std::string> f : filter) {

			if (get<1>(f) == '=') { //last instruction in filter, just do what it says
				if (get<3>(f) == "A") { sum += r.calcRangesSize(); }	//accepted, add ranges to the sum
				else if (get<3>(f) == "R") {}	//rejected, do nothing, r dies with this loop.
				else { rangeQueue.push(std::make_pair(r, get<3>(f))); }	//put back into the rangeQueue with the filter name.
				break;
			}

			/*//if this is finished, it'll be 1/4th the lines of code and scalable with number of variables without changing anything.
			if(get<1>(f) == '<'){
				if (partRangeVarMap[get<0>(f)].second < get<2>(f)) { //fully less than compare
					if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
					else if (get<3>(f) == "R") {}
					else { rangeQueue.push(std::make_pair(r, get<3>(f))); }
					break;
				}
				else if (partRangeVarMap[get<0>(f)].first < get<2>(f)) { //partially less than compare



				}
			}
			*/


			/*
			* LESS THAN
			*/
			if (get<1>(f) == '<') {
				if (get<0>(f) == 'x') {
					if (r.x.second < get<2>(f)) { //range fully less than compare
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }
						break;
					}
					else if (r.x.first < get<2>(f)) { //range only partially less than compare, make a new partrange
						D19partRanges s = r;	//make a copy of range r
						s.x.first = get<2>(f);	//change range s x.first to compare val
						rangeQueue.push(std::make_pair(s, filterName)); //put the new partrange into the queue, back onto the same filter.
						r.x.second = get<2>(f) - 1; //range r x.second is compare val - 1

						//process range r
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }

						break;
					}
					//otherwise, filter doesnt apply.
				}
				//if we could do this once for all the letters, that'd be nice
				if (get<0>(f) == 'm') {
					if (r.m.second < get<2>(f)) { //range fully less than compare
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }
						break;
					}
					else if (r.m.first < get<2>(f)) { //range only partially less than compare, make a new partrange
						D19partRanges s = r;	//make a copy of range r
						s.m.first = get<2>(f);	//change range s m.first to compare val
						rangeQueue.push(std::make_pair(s, filterName)); //put the new partrange into the queue, back onto the same filter.
						r.m.second = get<2>(f) - 1; //range r m.second is compare val - 1

						//process range r
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }

						break;
					}
					//otherwise, filter doesnt apply.
				}
				if (get<0>(f) == 'a') {
					if (r.a.second < get<2>(f)) { //range fully less than compare
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }
						break;
					}
					else if (r.a.first < get<2>(f)) { //range only partially less than compare, make a new partrange
						D19partRanges s = r;	//make a copy of range r
						s.a.first = get<2>(f);	//change range s a.first to compare val
						rangeQueue.push(std::make_pair(s, filterName)); //put the new partrange into the queue, back onto the same filter.
						r.a.second = get<2>(f) - 1; //range r a.second is compare val - 1

						//process range r
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }

						break;
					}
					//otherwise, filter doesnt apply.
				}
				if (get<0>(f) == 's') {
					if (r.s.second < get<2>(f)) { //range fully less than compare
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }
						break;
					}
					else if (r.s.first < get<2>(f)) { //range only partially less than compare, make a new partrange
						D19partRanges s = r;	//make a copy of range r
						s.s.first = get<2>(f);	//change range s s.first to compare val
						rangeQueue.push(std::make_pair(s, filterName)); //put the new partrange into the queue, back onto the same filter.
						r.s.second = get<2>(f) - 1; //range r s.second is compare val - 1

						//process range r
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }

						break;
					}
					//otherwise, filter doesnt apply.
				}
			}


			/*
			* GREATER THAN
			*/
			if (get<1>(f) == '>') {
				if (get<0>(f) == 'x') {
					if (r.x.first > get<2>(f)) { //range fully more than compare
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }
						break;
					}
					else if (r.x.second > get<2>(f)) { //range only partially more than compare, make a new partrange
						D19partRanges s = r;	//make a copy of range r
						s.x.second = get<2>(f);	//change range s x.first to compare val
						rangeQueue.push(std::make_pair(s, filterName)); //put the new partrange into the queue, back onto the same filter.
						r.x.first = get<2>(f) + 1; //range r x.second is compare val - 1

						//process range r
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }

						break;
					}
					//otherwise, filter doesnt apply.
				}
				if (get<0>(f) == 'm') {
					if (r.m.first > get<2>(f)) { //range fully more than compare
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }
						break;
					}
					else if (r.m.second > get<2>(f)) { //range only partially more than compare, make a new partrange
						D19partRanges s = r;	//make a copy of range r
						s.m.second = get<2>(f);	//change range s x.first to compare val
						rangeQueue.push(std::make_pair(s, filterName)); //put the new partrange into the queue, back onto the same filter.
						r.m.first = get<2>(f) + 1; //range r x.second is compare val - 1

						//process range r
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }

						break;
					}
					//otherwise, filter doesnt apply.
				}
				if (get<0>(f) == 'a') {
					if (r.a.first > get<2>(f)) { //range fully more than compare
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }
						break;
					}
					else if (r.a.second > get<2>(f)) { //range only partially more than compare, make a new partrange
						D19partRanges s = r;	//make a copy of range r
						s.a.second = get<2>(f);	//change range s x.first to compare val
						rangeQueue.push(std::make_pair(s, filterName)); //put the new partrange into the queue, back onto the same filter.
						r.a.first = get<2>(f) + 1; //range r x.second is compare val - 1

						//process range r
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }

						break;
					}
					//otherwise, filter doesnt apply.
				}
				if (get<0>(f) == 's') {
					if (r.s.first > get<2>(f)) { //range fully more than compare
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }
						break;
					}
					else if (r.s.second > get<2>(f)) { //range only partially more than compare, make a new partrange
						D19partRanges s = r;	//make a copy of range r
						s.s.second = get<2>(f);	//change range s x.first to compare val
						rangeQueue.push(std::make_pair(s, filterName)); //put the new partrange into the queue, back onto the same filter.
						r.s.first = get<2>(f) + 1; //range r x.second is compare val - 1

						//process range r
						if (get<3>(f) == "A") { sum += r.calcRangesSize(); }
						else if (get<3>(f) == "R") {}
						else { rangeQueue.push(std::make_pair(r, get<3>(f))); }

						break;
					}
					//otherwise, filter doesnt apply.
				}
			}
		}
	}

	return sum;
}