/*
 * Implementation for ClimbChromosome methods
 */

#include "climb_chromosome.hh"

#include <cassert>
#include <random>

using namespace std;

// Construct like Chromosome class
ClimbChromosome::ClimbChromosome(const Cities* cities_ptr)
  : Chromosome(cities_ptr)
{
  assert(is_valid());
}

// Destructor
ClimbChromosome::~ClimbChromosome(){
  assert(is_valid());
}

void ClimbChromosome::mutate() {
  double chrom_og = get_fitness(); // Evaluate the fitness of the current (original) chromosome
  uniform_int_distribution<unsigned int> distribution(0, order_.size()-1);
  unsigned int p = distribution(generator_); // Pick a random point p in the chromosome.
  Chromosome* variationOne = clone();
  if (p == 0) { // swap with the city at index N-1
    variationOne->swapVal(p,order_.size()-1);
  }
  else { // Swap the city at index p with the city at index p-1
    variationOne->swapVal(p,p-1);
  }
  double chromOne = variationOne->get_fitness(); // evaluate resulting chrom's fitness
  Chromosome* variationTwo = clone();
  if(p == order_.size()-1) { // If p==N-1, swap with the city at index 0 instead of at index N.
    variationOne->swapVal(p,0);
  }
  else { // Swap the city at index p (from the original chromosome) with the city at index p+1
    variationOne->swapVal(p,p+1);
  }
  double chromTwo = variationTwo->get_fitness(); // Evaluate resulting chrom fitness
  // Choose the fittest chromosome of the three as the resulting mutated chromosome
  // if original chromosome is fittest, void, nothing happens
  if (chromOne > chrom_og && chromOne > chromTwo) {
    order_ = variationOne->get_ordering();
  }
  else if (chromTwo > chrom_og){
    order_ = variationTwo->get_ordering();
  }
}
