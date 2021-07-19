/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "deme.hh"
#include <random>
#include <chrono>

using namespace std;

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
  : mut_rate_(mut_rate)
{
  for (unsigned int i = 0; i < pop_size; i++) {
    Chromosome* chrom = new ClimbChromosome(cities_ptr); // new Chromosome pointer based on cities_ptr for city coords
    pop_.push_back(chrom); // Add the new chromosome to the population vector
  }
}

// Clean up as necessary
Deme::~Deme()
{
  for (unsigned int i = 0; i < pop_.size(); i++) { // Destructor deletes the pointers and vector
    delete pop_[i];
    pop_.clear();
  }
}

// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
  std::vector<Chromosome*> pop_2; // Vector for children
  for (unsigned int i = 0; i < pop_.size()/2; i++) {
    auto p1 = select_parent();
    auto p2 = select_parent();
    // generate a number from 0.0 to 1.0
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (r < mut_rate_) {
      p1->mutate();
    }
    // generate a diff number from 0.0 to 1.0
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (r2 < mut_rate_) {
      p2->mutate();
    }
    // recombine the 2 chosen chromosomes from select_parent to generatea new
    // pair of chromosomes
    auto children = p1->recombine(p2);
    pop_2.push_back(children.first);
    pop_2.push_back(children.second);
  }
  pop_ = pop_2; // delete all the old chromsomes of pop_ with the newly generated chromosomes
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  Chromosome* chrom = pop_[0];
  double bestFitness = pop_[0]->get_fitness();
  for(unsigned int i = 1; i < pop_.size(); i++) {
    if (pop_[i]->get_fitness() > bestFitness){
      bestFitness = pop_[i]->get_fitness();
      chrom = pop_[i];
    }
  }
  return chrom;
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
  double fitnessSum = 0;
  for(unsigned int i = 0; i < pop_.size(); i++) {
    fitnessSum += pop_[i]->get_fitness(); // add fitness of all chromosomes
  }
  // generate a number from 0.0 to fitnessSum (favors fitter chromosomes (potential parents))
  float number1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/fitnessSum);
  for (unsigned int j = 0; j < pop_.size(); j++) {
    number1 -= pop_[j]->get_fitness();
    // if the fitness of a chromosome in pop_ is greater than the randomly
    // generated number from 0.0 to fitnessSum, then return a pointer to that
    // chromosome as the parent
    if (number1 <= 0) {
      return pop_[j];
    }
  }
  return nullptr;
}

// This method was for testing since we needed pop_.size(), but it's private and
// can't be accessed by main
// vector<Chromosome*> Deme::get_pop() {
//   return pop_;
// }

// int main() {
//   // testing for Deme
//
//   Cities cities("challenge.tsv");
//   Cities* cities2 = &cities;
//   Deme* d = new Deme(cities2, 100, 0.5);
//   // cout << "first gen:" << "\n";
//   // for (long unsigned int i = 0; i < d->get_pop().size(); i++) {
//   //   cout << d->get_pop()[i]->get_fitness() << "\n";
//   // }
//   // cout << "most fit:" << "\n";
//   double firstNumber = d->get_best()->get_fitness();
//   //cout << "next gen:" << "\n";
//   // for (long unsigned int i = 0; i < d->get_pop().size(); i++) {
//   //   cout << d->get_pop()[i]->get_fitness() << "\n";
//   // }
//   for (auto i = 0; i < 100; i++) {
//     d->compute_next_generation();
//   }
//   double lastNumber = d->get_best()->get_fitness();
//   if (lastNumber > firstNumber) {
//     cout << "True" << "\n";
//   }
//   else {
//     cout << "False" << "\n";
//   }
//
//   // testing for Chromosome
//
//   // Cities cities("challenge.tsv");
//   // Cities* cities2 = &cities;
//   // Chromosome* chrom = new Chromosome(cities2);
//   // cout << chrom->get_fitness() << "\n";
//   // chrom->mutate();
//   // cout << chrom->get_fitness() << "\n";
//   // cout << "mutate works!!!!!" << "\n";
//   // Cities cities3("challenge.tsv");
//   // Cities* cities4 = &cities3;
//   // Chromosome* chrom2 = new Chromosome(cities4);
//   // auto children = chrom->recombine(chrom2);
//   // cout << children.first->get_fitness() << "\n";
//   // cout << children.second->get_fitness() << "\n";
//   // cout << "reached the end!" << "\n";
//   return 0;
// }
