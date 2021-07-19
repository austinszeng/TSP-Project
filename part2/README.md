# Traveling Salesperson Problem (Part 2)

This is our attempt at CSCI 221's Homework 10 assignment, TSP project part 2. Our group was comprised of Austin Zeng, Genevieve Moore, and Keith Ng.

We opted to use Eitan's code for cities and tsp.

## Compiling Instructions

All files can be compiled with `make` in the terminal. The Makefile creates an executable `./tsp`, which can be run on tsv files.  

## Added Functions and Methods

### Chromosome class
<details>
<summary>is_valid checks that a created permutation does not have any repeats or gaps within it.
</summary>
<br>
- First, it copies the given order, then it sorts the order numerically. Finally, in a for loop, the sorted values in the order are checked against an increasing index counter.
- If a value and an index counter don't match up, is_valid returns false. If it has checked all the values without a problem, it returns true.
</details>

<details>
<summary>get_fitness returns the fitness score of a given permutation. Our current number calculates the score by comparing it to the fitness score of the original challenge.tsv permutation.
</summary>
<br>
- get_fitness uses total_path_distance from the Cities class. The variable "original" is set to 27125.9 because this was the distance of the original challenge.tsv order. The method divides the original distance by the the new calculated distance to give a fitness score, usually around 1.
- A score higher than 1 means the ordering is better than the original path, a score less than 1 means the path is worse.
</details>

<details>
<summary>mutate swaps two random points in a permutation in order to change the ordering without creating repeats.
</summary>
<br>
- mutate randomly generates 2 values, checks that they are different numbers, then switches the cities at these points.
</details>

<details>
<summary>recombine creates two children from two parents.
</summary>
<br>
- The method calculates a random range and takes traits from a parent in that range, then takes the remaining traits from the other parent to create a child. The second child uses the same range but takes it from the opposite parents instead.
</details>

<details>
<summary>is_in_range checks if a value is within a given range.
</summary>
<br>
- This helper function is used in create_crossover_child (which in turn is a helper function to recombine) to check if a given number is within a given range. It does this by checking the input number against each number within the range. If a value in the range matches the input number, the function returns true. If the function goes through each value and no numbers match, the function returns false.
</details>

### Deme class
<details>
<summary>get_best finds the chromosome with the highest fitness score and creates a copy of it.
</summary>
<br>
- Using the get_fitness method from Chromosome, get_best uses a for loop to compare each fitness score with a running "best" score. Every time a calculated score for a new chromosome is higher than the current "best" chromosome, the new chromosome becomes the best chromosome.
- After going through all the chromosomes, the method returns the chromosome with the highest fitness.
</details>

<details>
<summary>select_parent selects a random parent for reproduction.
</summary>
<br>
- This method counts the total fitness of all the chromosomes in a population, then stores it in the fitnessSum variable. It then generates a number within the range of 0 to the fitnessSum. Finally, in a for loop, the fitness score of chromosomes in the population is subtracted from the random number until the sum reaches 0, then it returns the chromosome that subtracted last, making this the next parent.
</details>

<details>
<summary>compute_next_generation replaces the old population with a new generation of child chromosomes
</summary>
<br>
- This method uses the previously mentioned select_parent method to pick 2 parents randomly, then it attempts to mutate these parents (mutation chance is determined mutation rate and a randomly generated number). The two parent chromosomes reproduce when the "recombine" method is called. Finally, these children replace the old generation.
</details>

## Analyzing Our Comparison Chart

The included file `comparison.gif` displays our chart created with gnuplot. It shows the comparison between a search for the best path with a random algorithm and a genetic algorithm.

![Alt Text](https://cdn.discordapp.com/attachments/837826377389965333/839326078480285717/comparison.gif)

As the plot suggests, within the same number of iterations, a genetic algorithm is able to find a shorter path (with a total distance of 18686.8) versus the algorithm that creates random paths (which has a total distance of 19214.8).
