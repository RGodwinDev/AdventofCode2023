#include "./headers/Day20.h"

int Day20::day() {
	std::string line;
	std::fstream file("./inputs/day20input.txt");
	int lines = 0;
	int sum1 = 0, sum2 = 0;

	std::vector<std::string> input;
	while (getline(file, line)) {
		lines++;
		input.push_back(line);
	}
	// % is a flip flop module
	// flip flops can be either on or off, initially off
	// if a flip flop gets a high pulse, it ignores it
	// if it recieves a low pulse, it flips between on/off
	// if it was off, it turns on and sends a high pulse
	// if it was on, it turns off and sends a low pulse
	// 
	// & is a conjunction module
	// remembers the most recent pulse from all their connected INPUT modules
	// as in, any module that has this module as a destination.
	// default is all connected modules are low.
	// When a pulse is received, the conjunction module remembers the input and pulse type
	// if all inputs are high pulses, the conjunction module sends a low pulse
	// otherwise, it sends a high pulse
	// 
	// broadcaster is the broadcast module, there's only 1
	// the broadcaster sends the pulse it recieved to all its destination modules
	// 
	// when the button module is pushed, a low pulse is sent to the broadcaster
	// while the modules are processing, do not press the button again.
	
	// determine how many low and high pulses are sent after pushing the button 1000 times.
	// whats the answer if you multiply low pulses * high pulses.

	std::vector<std::string> flipflops;
	std::vector<std::string> conjunctions;
	std::vector<std::string> broadcasters;
	for (std::string s : input) {
		if (s[0] == '%') { //flipflop module 
			flipflops.push_back(s);
		}
		else if (s[0] == '&') { //conjunction module
			conjunctions.push_back(s);
		}
		else { //the broadcaster module
			broadcasters.push_back(s);
		}
	}




	std::cout << "Day 20:\t" << sum1 << "\tand " << sum2 << std::endl;
	return lines;
}