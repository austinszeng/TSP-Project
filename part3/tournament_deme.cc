/*
 * Implementation for TournamentDeme methods
 */

#include "tournament_deme.hh"

#include <algorithm>
#include <random>
#include <chrono>
#include <math.h>
#include <vector>
#include <cassert>

using namespace std;

// Generate a TournamentDeme of the specified size with all-random chromosomes like Deme class.
TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
  : Deme(cities_ptr, pop_size, mut_rate)
{
}

TournamentDeme::~TournamentDeme()
{
  for (unsigned int i = 0; i < pop_.size(); i++) { // Destructor deletes the pointers and vector
    delete pop_[i];
    pop_.clear();
  }
}

// Helper function that checks in an input is a power of 2
bool TournamentDeme::isPow2(long unsigned int input) {
  if (input > 0) {
    while (input % 2 == 0) {
      input = input / 2;
    }
    if (input == 1) {
      return true;
    }
  }
  if (input == 0 || input != 1) {
    return false;
  }
  return false;
}

Chromosome* TournamentDeme::select_parent(){
  // Select the number of parents
  long unsigned int numParents = 2;
  // Ensure the number of parents is not more than the population and is a power of 2
  assert(numParents <= pop_.size());
  assert(isPow2(numParents) == true);

  vector<Chromosome*> popClone = pop_;
  random_shuffle(popClone.begin(), popClone.end()); // randomize list of parents

  vector<Chromosome*> chosenParents; // Create an empty list to store the chosen parents
  for (unsigned int i = 0; i < numParents; i++) {
    chosenParents.push_back(popClone[i]); // Add a parent to the list at the index
  }
  // Repeat process of choosing better parent of a pair until only one parent left
  while (1 < chosenParents.size()) {
    auto parent1 = chosenParents.front(); // Parent 1 and Parent 2 are the first 2 elements in the list
    chosenParents.erase(chosenParents.begin()); // Remove the parents after they have been set
    auto parent2 = chosenParents.front();
    chosenParents.erase(chosenParents.begin());
    // add fitter parents of each pair to new list
    if (parent1->get_fitness() > parent2->get_fitness()) {
      chosenParents.push_back(parent1);
    }
    else {
      chosenParents.push_back(parent2);
    }
  }
  return chosenParents.front();
}
