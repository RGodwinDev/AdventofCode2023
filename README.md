# AdventofCode2023
https://adventofcode.com/2023

The main() is in AdventofCode2023Day1/AdventofCode2023.cpp

ignore the 'Day1', all of the days are in this project.

![alt text](https://github.com/FinalFlashLight/AdventofCode2023/blob/master/AdventofCode2023Day1/screenshots/ssday6.png)

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
		if you have 4 copies of card 1, you get 4 copies of each card 2,3,4,5.
		We need to keep track of how many copies of each card we win.
		Copied cards are scored exactly the same as original cards.
		Add up how many cards we end up with TOTAL.

Day5 - If You Give A Seed A Fertilizer

	Part 1
		transform a seed thru several filters, and return the smallest one after transforming.
		I put the seeds into a vector<__int64> and made tuples from the filter inputs.
		(destination, source, range)
		I then went thru each filter with each seed, 
		seeing if that filter applying to the seed, and transforming if it did.
		At the end, just loop thru the seeds and see which one ended up the smallest.


	Part 2
		transform ranges of seeds thru ranges of filters and return the smallest seed.
		This one was significantly harder than the previous 4 days.
		This time I put the seeds into a vector<pair<__int64, __int64>>,
		first is starting seed of the range, second is size of the range of seeds
		
		use the same filter tuples.
		sort the filter tuples in each filter step.

		for each filter step
			for each seedrange in seedranges
				for each individual filter in a filter step

					if seedrange completely covers filter
					if seedrange is completely inside filter
					if just start of seedrange is in filter
					if just end of seedrange is in filter

					put before filter and inside filter ranges in newSeedRange
					put after filter range back into seedrange vector to be processed later
				if the seedrange wasnt filtered at all, put into newSeedRange as is	
					
			after each filterstep
			sort newSeedRange
			seedranges = newSeedRange
			sort seedrange //probably not needed

		at the end, get the smallest seed in seedrange!
		because we sorted, it should be the first one.

		I think my dataset got mixed wrong or something. No matter how I cut it, the answer is 0.
		Interestingly, if I print out my vector and choose first number that isnt 0, it's the correct answer.
		Other people on the advent of code subreddit complained about the same issue.

		I think I've fixed the major bugs :O

	Ways I could make part1 and part2 faster
		binary search the filters
		For part1 that would be pretty easy. Would change it from O(seed*filters) to O(seedlogfilters)
		For part2 it would probably be significantly more complicated
		because we're dealing with ranges instead of single numbers. 

Day 6 - Wait For It
	
	significantly easier than yesterday.
	Part 1
		You enter a boat race! But the boats have a ramp up time.
		Every millisecond you wait to launch your boat, 
		your boat will go faster by 1 millimeter per millisecond!

		The goal of the race is to go as far as possible in the time given.
		Youre given a paper with times for each race, and the best distance someones gotten in that race.
		Count how many ways you can beat each race, and multiply them together.

	Part 2
		Jokes on you! The times and distances on the paper was actually a single race!
		Calculate the ways to win that one race.

		I just brute forced both part1 and part2, although I know there is an O(1) solution out there.
