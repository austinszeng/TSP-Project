/*
 * Header file for the ClimbChromosome class, which inherits from the
 * Chromosome class and overrides the mutate and clone methods
 */

#pragma once

#include "chromosome.hh"

class ClimbChromosome : public Chromosome {
  public:
    // constructor
    ClimbChromosome(const Cities*);

    // virtual destructor
    virtual ~ClimbChromosome();

    // Search for best solution in a small local “neighborhood” of the current chromosome
    // It works as follows (assuming N cities, i.e. a chromosome with N genes):
    // 1. Evaluate the fitness of the current (original) chromosome
    // 2. Pick a random point p in the chromosome.
    // 3. Swap the city at index p with the city at index p-1 and evaluate the
    //    resulting chromosome's fitness. If p==0, swap with the city at index N-1
    //    instead of at index -1.
    // 4. Swap the city at index p (from the original chromosome) with the city at
    //    index p+1 and evaluate the resulting chromosome's fitness. If p==N-1,
    //    swap with the city at index 0 instead of at index N. (hint: use modulus).
    // 5. Find which of the three chromosomes (i.e., chromosomes from steps A, C, and D)
    //    produced the fittest ordering and choose that fittest chromosome as the
    //    resulting mutated chromosome.
    virtual void mutate() override;

    // Override clone to return new ClimbChromosome instead of new Chromosome
    // Both still point to a Chromosome*
    virtual Chromosome* clone() const override {
      return new ClimbChromosome(cities_ptr_);
    }
};
