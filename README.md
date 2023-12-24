# AdventofCode2023
https://adventofcode.com/2023

Stars achieved so far 12/22/23 - 31/44

The main() is in AdventofCode2023Day1/AdventofCode2023.cpp

ignore the 'Day1', all of the days are in this project.

Ran on an AMD FX-8350, cpu from 2012
![alt text](https://github.com/FinalFlashLight/AdventofCode2023/blob/master/AdventofCode2023Day1/screenshots/ssday19.png)

Day1 - Trebuchet?! **

	Part 1
		find the first digit from left and right side of each string, and put them together.
		example string: "four8seven2one" would result in 8 and 2, making 82.
		I just scanned the string from the left, until I found a digit with isdigit()
		And then scanned it from the right.

	Part 2
		Same thing but this time, words also count as numbers.
		For the same example string, "four8seven2one", the result would be 4 and 1, making 41.
		This time when I scanned, if the char was not a digit 
		I checked if the substring starting at the char was equal to a word number.

Day2 - Cube Conundrum **

Day3 - Gear Ratios **

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

Day4 - Scratchcards **

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

Day5 - If You Give A Seed A Fertilizer **

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


Day 6 - Wait For It **
	
	Part 1
		The goal of the race is to go as far as possible in the time given.
		Count how many ways you can beat each race, and multiply them together.

	Part 2
		The times and distances on the paper was actually a single race!
		Calculate the ways to win that one race.
		I just brute forced both part1 and part2, although I know there is an O(1) solution out there.

	I changed from bruteforce to using the quadratic formula everyone else was using.
	It now runs about 1ms instead of ~125ms.
	I also implemented parsing from a file instead of hard coding the numbers in.

Day 7 - Camel Cards **

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

Day 8 - Haunted Wasteland **
	
	Part 1
		A map traversal, we check the map for our location, and go left or right, depending on the directions we're given.
		Start at AAA and count how many steps until we end up at ZZZ.
		All locations went into a map<string, pair<string,string>>, where the key was current location,
		and the pair was the left/right next location. Just traverse until we get to ZZZ.

	Part 2
		We start at every node that ends with A, and want to know when ALL ghosts are on nodes that end with Z.
		I looked at the solution thread to figure out we use Least Common Multiple(LCM) for this.
		Calculate each ghosts A to Z distance, then calculate the LCM of all those distances.
		While the LCM works and is the answer, 
		it's technically flawed because there is a possibility all the ghosts just happen to land on Zs before the LCM.

Day 9 - Mirage Maintenance **

	Part 1
		We have several sequences of numbers, 
		and want to know the next number in each of the sequences.

		This problem has just a couple steps.
		Generate the differences and predict the next number.
		Answer is the sum of the predicted 1st next numbers from all the sequences.

	Part 2
		While looking forward is nice, we want to predict what has already happened!
		Most of the logic is already done in part 1, just work backwards instead.

	Edit: removed attempts at concurrency, they weren't going anywhere lol.

Day 10 - Pipe Maze **

	Part 1
		First thing I do is find 'S' to get a start position.
		From there I traverse the pipe until we get back to 'S', counting steps along the way.
		Then it's a simple steps/2. +1 if odd.

	Part 2
		Now we want to know the area inside the pipe.
		For this I made a second vector of the pipe, but sorted. This allows us to binary search the pipe later.
		We now have 2 vectors of the pipe, one in traversal order, and the other in sorted order.
		From here we need to find the pipe. From the top of the map, go down until we run into a piece of the pipe.
		Now we know this piece of pipe is above another piece of the pipe, because the pipe is a circle.
		So to find the area, we just look below this piece of the pipe. 
		check if this area is part of the pipe, and if it's not it's confirmed within the pipes boundarys.
		Keep going until we run into the pipe again.

		We ONLY need to check below the pipe when moving WEST, 
		otherwise we would be counting the same squares multiple times.
		Once we make the loop once, we're done.


Day 11 - Cosmic Expansion **

	Part 1

	Part 2

Day 12 - Hot Springs *

	Part 1
		I brute forced by checking every combination of optionals and checking if each combo was valid.
		Takes about 45 seconds.
	
	Part 2
		LOL, The brute force method ran for a good while and didn't even get past the first line.

Day 13 - Point of Incidence **

	Part 1
		Find the reflection in each mirror and sum the location of each reflection line.
		This is very similar to checking if a string is a palindrome. 
		Except we're checking if rows/columns are the same until the edge.

	Part 2
		Very similar to part 1, but we can change one character from # to . or . to #, creating a new line.
		I used part 1, but allowed 1 error in the palindrome to exist.
		Also the line must be a new reflection line, not the same from part 1.

Day 14 - Parabolic Reflector Dish *

	Part 1
		Pretty easy, just make a tiltNorth function that rolls rocks upwards, then calculate the weight.
		
	Part 2
		Now create a spincycle() that tilts north->west->south->east. Do it 1 billion times...
		Creating spincycle was actually easy, but running 1 billion times would take my computer over a month.
		I know the answer has to do with detecting a cycle,
		and then calculating where in the cycle we will be after 1 billion times.

Day 15 - Lens Library ** 

Day 16 - The Floor Will Be Lava **
	
	This could have been smarter, but this works.
	Part 1
		I did part 1 by creating a grid<tile>. 
		Then I shoot a beam into the grid at 0,0 going east.
		Any tiles it hits get marked as energized.
		Any time we hit a splitter, we add another beam to the beam queue.
		If a beam goes out of bounds or runs into an energized tile from a direction
		that it's been hit from before, the beam is killed.
		Keep going until the beam queue is empty.
		Afterwards, we count how many tiles are energized.

	Part 2
		Same as part 1, but for each possible starting position we make a copy of the original grid, 
		then traverse it from the respective start position and count the energized tiles.

Day 17 - Clumsy Crucible

	Part 1
		This is pathfinding with the restriction that we can move max 3 times in a direction before having to turn.

Day 18 - Lavaduct Lagoon

	Part 1
		This problem feels similar to Day 10. We just want the area within the edges.
		Haven't gotten around to finishing this one yet.

Day 19 - Aplenty *
	
	Part 1
		I created a map of filters, then added the parts to a partqueue
		All the parts start with the "in" filter
		Any parts accepted by the filter go in an accepted pile.
		Any parts requiring further filtering go back in the part queue.
		Any rejected parts just get thrown away. I had a rejection pile but it didn't get used.
		The answer is the sum of values from all the accepted parts.

	Part 2
		Dealing with ranges, similar to Day5. 
		All the values for each part can be between 1 and 4000.
		Calculate how many possible part value combinations are accepted.

		There's 3 basic things we check for on each filter.
		A range is fully less/greater than the compare.
		A range is partially less/greater than the compare.
		A range is not in the compare at all.

		If a range is fully less or greater than the compare,
		We accept/reject or give the range to another filter.

		If a range is partially less or greater than the compare,
		we break the range into 2, 
		accept/reject/give the range that is inside the compare
		and put the range outside the compare back into the queue at the same filter.

		If a range is fully outside the compare, 
		it continues onto the next instruction until we get to the last instruction in the filter.
		
		If we get to the last instruction, we accept/reject/give the range, per the instruction.

Day 20 - Pulse Propagation

Day 21 - Step Counter

Day 22 - Sand Slabs

Day 23 - A Long Walk

Day 24 - 

Day 25 -