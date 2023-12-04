# AdventofCode2023
https://adventofcode.com/2023

ignore the 'Day1', it's all days in this project.

![alt text](https://github.com/FinalFlashLight/AdventofCode2023/blob/master/AdventofCode2023Day1/screenshots/ssday4.png)

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

Day4 - Scratchcards

	Part 1
	    Card   1: 30 48 49 69  1 86 94 68 12 85 | 86 57 89  8 81 85 82 68  1 22 90  2 74 12 30 45 69 92 62  4 94 48 47 64 49
	    numbers left of '|' are winning numbers, right are playable numbers. count how many winning numbers are in playable numbers.
	    the first match is worth 1 point, then further matches double your points. 2^(matches-1)
	    add up how much all the cards are worth
	
	Part 2
		The cards actually act different now. The amount of times you win gets you copies of cards below it.
		if you win 4 times on card 1, you get 1 copy each of card 2,3,4,5.
		We need to keep track of how many copies of each card we win.
		Copied cards are scored exactly the same as original cards.
		Add up how many cards we end up with TOTAL.
		
	
