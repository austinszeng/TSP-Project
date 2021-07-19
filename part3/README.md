# Traveling Salesperson Problem (Part 3)

This is the code for CSCI 221's Homework 11 assignment, TSP project part 3. Our group consisted of Austin Zeng, Genevieve Moore, and Keith Ng.

We used Eitan's solutions for cities and tsp, but we used our own previous solutions in part 2 for chromosome and deme.

## Compiling Instructions

All files can be compiled with `make`. The Makefile creates an executable `./tsp`, which can be run on tsv files.

## Added Functions and Methods

### ClimbChromosome class

The ClimbChromosome class is very similar to the Chromosome class it inherits from except that the mutate() and clone() methods have been altered in order to create better chromosomes.

- The mutate() method now mutates the chromosome using "local hill climbing" by choosing a random city in the chromosome, swapping cities within that chromosome and calculating the fitness of that Chromosome. It does this on several other chromosomes, then compares these chromosomes with each other. The chromosome with the best fitness score is chosen as the mutation.
- The altered clone() method now returns a new ClimbChromosome (instead of a Chromosome).

### TournamentDeme class

The TournamentDeme class inherits from the Deme class but changes the select_parent() method in order to choose better parents

- The new select_parent() method takes in a subset from the population (the size of the subset must be a power of 2). It then takes the first two elements of the subset and compares their fitness score. The chromosome with a higher score goes back into the subset while the other is deleted. The method does this on the subset until only 1 chromosome remains, then this chromosome is chosen for breeding.
- We also implemented a helped function, isPow2, which checks that the selected subset size is actually a power of 2.

## Analyzing Our Comparison Chart

`comparison.gif` shows out results graphed with gnuplot. It takes data from our original genetic algorithm, genetic algorithm with the ClimbChromosome class, and genetic algorithm with the TournamentDeme class.

![Alt Text](https://cdn.discordapp.com/attachments/837826377389965333/842172716153176064/comparison.gif)

Our graph shows that the local.tsv line, which represents the results using ClimbChromosome instead of Chromosome, finds better solutions than out original search, within less iterations as well. Furthermore, tournament.tsv, which displays our results using TournamentDeme instead of Deme, produces even better results, in significantly less iterations!

Interestingly, we found that a lower P size for TournamentDeme yielded better results than using a higher value.  
