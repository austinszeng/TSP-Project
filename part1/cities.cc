#include "cities.hh"
#include <math.h>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
Cities::Cities()
{
}

//////////////////////////////////////////////////////////////////////////////
Cities::~Cities()
{
}

int Cities::get_cities_size(){
  return cities_.size();
}

double euclDist(Cities::coord_t firstCoord, Cities::coord_t secCoord){
  double eDist = hypot(secCoord.first - firstCoord.first, secCoord.second - firstCoord.first);
  return eDist;
}

//////////////////////////////////////////////////////////////////////////////
double Cities::total_path_distance(const permutation_t& ordering) const {
  double dist = 0;
  Cities::coord_t firstCity = cities_[ordering[0]];
  for (long unsigned int i = 1; i < ordering.size(); i++) {
    Cities::coord_t secondCity = cities_[ordering[i]];
    //euclidean distance
    dist += euclDist(firstCity, secondCity);
    firstCity = cities_[ordering[i]];
  }
  // Add the distance going back from the last city in the permutation to the first one.
  Cities::coord_t secondCity = cities_[ordering[0]]; // reset to first city
  dist += euclDist(firstCity, secondCity);
  return dist;
}

//////////////////////////////////////////////////////////////////////////////
Cities Cities::reorder(const permutation_t& ordering) const {
  Cities city;
  for (long unsigned int i = 0; i < ordering.size(); i++) {
      city.cities_.push_back(cities_[ordering[i]]);
  }
  return city;
}

//////////////////////////////////////////////////////////////////////////////
Cities::permutation_t Cities::random_permutation(unsigned int len) {
  Cities::permutation_t p;
  // random number generator constructed from time-based seed
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static default_random_engine generator (seed);

  uniform_int_distribution<unsigned int> distribution(0, len-1);
  while (p.empty() || p.size() < len) { // "p.empty() ||" so function doesn't access memory we don't have
    bool newNumber = true;
    unsigned int number = distribution(generator);
    if (!(p.empty())) {
      // same_ind = std::find(p.begin(), p.end(), number) // using STL
      // if (same_ind != p.end()) {
      //   newNumber = false;
      //   break;
      // }
      for (long unsigned int i=0; i < p.size(); i++) { // check if the RNG produces the same index
        if (p[i] == number) { // if same index, don't add index to permutation
          newNumber = false;
          break;
        }
      }
    }
    if (newNumber){ // if not same index, add number to permutation
      p.push_back(number);
    }
  }
  return p;
}
