/*
 * Header file for the TournamentDeme class, which inherits from the
 * Deme class and overrides the select_parent method
 */

#pragma once

#include "deme.hh"

class TournamentDeme : public Deme {
  public:
    // Takes same arguments as the constructor for Deme
    TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);

    // virtual destructor
    virtual ~TournamentDeme();

    // Helper function
    bool isPow2(long unsigned int input);

    // override whatever is necessary to replace the parent selection algorithm
    // Tournament selection:
    // A. Select P parents at random, where P is a constant power of two that you
    //    choose (no bigger than the population size).
    // B. Take the first pair in the set of P parents and discard the parent with
    //    the lower fitness of the two.
    // C. Do the same for the next pair, and so forth. You should have P/2 parents
    //    in the resulting set.
    // D. Repeat steps B--C until you’re left with only one parent.
    virtual Chromosome* select_parent() override;
};
