# AdventofCode2023
https://adventofcode.com/2023

The main() is in AdventofCode2023Day1/AdventofCode2023.cpp

ignore the 'Day1', all of the days are in this project.

Ran on an AMD FX-8350, cpu from 2012
![alt text](https://github.com/FinalFlashLight/AdventofCode2023/blob/master/AdventofCode2023Day1/screenshots/ssday11.png)

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

Day 5b - If you Give A Seed A Fertilizer (RBTree edition)

	Part 1b
		I've written a red black tree to handle the filters.
		But only the necessary parts for part 1 to work.
		Now when the seeds get filtered, it's just a binary search instead of linear searching the filters.
		I had a bug for a good hour where a grandparent node mysteriously didn't existing when it should have.
		In the d5RBtreeNode::setChild method, I had somehow mixed up the left/right and was setting the wrong child.

	Part 2b has yet to be implemented
		Things I would need to do: 
		find out if filters overlap at all, if they do:
			update the RBTree.insert to adjust filters based on overlapping filters
			finish the RBTree remove functions, we really only have insert and balancing.
		write a new RBTree.part2Filter() that handles the seed ranges.
		seed range merging after all the ranges ran thru a filter.


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

	I changed from bruteforce to using the quadratic formula everyone else was using.
	It now runs about 1ms instead of ~125ms.
	I also implemented parsing from a file instead of hard coding the numbers in.

Day 7 - Camel Cards

	Part 1
		This one has a few parts to it. First is the obvious, parse the file.
		We need to give each hand of cards a type based on the combinations of cards in the hand.

		7 ranks of hands:

		5 of a kind
		4 of a kind
		Full House, 3 of a kind and a pair
		3 of a kind
		2 pairs
		1 pair				
		All cards unique

		Then we sort the hands by rank, and then by highest card in the hand from left to right.
		It's important to know that we do NOT sort the individual cards in the hands themselves.

		I had to write a customHandCompare function to handle this. 
		Getting sort() to accept it was the worst part.
		Turned out all I had to do was declare it a static function in the header.

	Part 2
		'J' is now a joker instead of jack. When choosing the type of the hand,
		the joker can act as any card it wants to.
		This lead to me making about 20 if statements all relating to the jokers.
		Also while sorting, 'J' only counts for 1 point. Any other card will beat it.

		Besides that tho the logic is basically the same from Part1.
		We do have to make another vector of hands though to run Part1 and Part2 at the same time.

Day 8 - Haunted Wasteland

Day 9 - Mirage Maintenance

	Part 1
		We have several sequences of numbers, 
		and want to know the next number in each of the sequences.

		This problem has just a couple steps.
		Generate the differences and predict the next number.
		Answer is the sum of the predicted 1st next numbers from all the sequences.

	Part 2
		While looking forward is nice, we want to predict what has already happened!
		Most of the logic is already done in part 1, we can just use it

Day 10 - Pipe Maze

Day 11 - Cosmic Expansion

Day 12 - Hot Springs

	This is the first puzzle that I truly don't know how to complete well.