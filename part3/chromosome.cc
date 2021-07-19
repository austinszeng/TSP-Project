/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>
#include <chrono>
#include <iostream>

#include "chromosome.hh"
#include "cities.hh"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
// random number generator constructed from time-based seed
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size())),
    generator_(seed) // construct generator from seed rather than rand()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
  assert(is_valid());
}

void Chromosome::swapVal(int num1, int num2) {
  auto placeholder = order_[num1];
  order_[num1] = order_[num2];
  order_[num2] = placeholder;
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
// Pick two points in the permutation at random and swap their values
void
Chromosome::mutate()
{
  uniform_int_distribution<unsigned int> distribution(0, order_.size()-1);
  unsigned int number1 = distribution(generator_);
  unsigned int number2 = distribution(generator_);
  // check that number1 and number2 are not equal
  while (number1 == number2) {
    number1 = distribution(generator_);
    number2 = distribution(generator_);
  }
  // swap
  auto order_copy = order_[number1];
  order_[number1] = order_[number2];
  order_[number2] = order_copy;

  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
  assert(is_valid());
  assert(other->is_valid());
  // Generate random numbers using generator_
  uniform_int_distribution<unsigned int> distribution(0, order_.size()-1); // range
  unsigned int b = distribution(generator_);
  unsigned int e = distribution(generator_);
  // [b,e), so e can't be less than or equal to b
  while (e <= b) {
    b = distribution(generator_);
    e = distribution(generator_);
  }
  // Create the two children with parents swapped for the second child
  Chromosome* childOne = create_crossover_child(this, other, b, e);
  Chromosome* childTwo = create_crossover_child(other, this, b, e);
  assert(childOne->is_valid());
  assert(childTwo->is_valid());
  return make_pair(childOne,childTwo);
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i]; //Takes traits from p1
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j; // skips numbers already taken from p1
      }
      assert(j < p2->order_.size());
      child->order_[i] = p2->order_[j]; // Takes traits from p2
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  // This number is the distance of challenge.tsv without modification. So,
  // unmodified, challenge.tsv has a score of 1. Better orders will receive
  // higher scores, e.g. 20000 would get a score of 1.36
  double original = 27125.9;
  double fitness_score = original/(this->calculate_total_distance());
  return fitness_score;
}

// A chromosome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
// We implement this check with a sort, which is a bit inefficient, but simple
bool
Chromosome::is_valid() const
{
  auto order_copy = order_; // sort a copy of order_ from least to greatest
  std::sort(order_copy.begin(), order_copy.end());
  // Since order_ should include all numbers from 0-[the size of order_-1],
  // the elements of order_copy should correspond to the iteration value
  for (long unsigned int i = 0; i < order_copy.size(); i++) {
    if (order_copy[i] != i) {
      return false;
    }
  }
  return true;
}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  for (unsigned int i = begin; i < end; i++) {
    if (order_[i] == value) {
      return true;
    }
  }
  return false;
}
