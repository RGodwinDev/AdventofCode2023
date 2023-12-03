# AdventofCode2023
https://adventofcode.com/2023

ignore the 'Day1', it's all days in this project.


Day1 - Trebuchet?!

Day2 - Cube Conundrum

Day3 - Gear Ratios

	..../ <- we check all the characters around a number, 
	.123.    if it's not another digit and not a '.', we assume it is a symbol.
	....*    if we confirm the number is next to a symbol, we add the number to sum1
	    ^- if the symbol is a star, we calc the position of the star, and add the position to the map.
		   at that position in the gearmap, we add the number to the associated vector

		pos of gear     numbers next to the gear at pos
	map<pair<int, int>, vector<int>> gears
			
	after going thru the entire input, we iterate thru the map of gear positions.
	at each position, if the vector has at least 2 numbers, 
	we multiply them together and add the product to sum2

Day4 - ???
		
