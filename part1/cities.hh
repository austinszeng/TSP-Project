/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <iostream>
#include <fstream>

// Representation of an ordering of cities
class Cities {
 public:
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;
  using cities_t = std::vector<coord_t>;
  // An ordering of the cities in cities_t. Each value represents a unique index
  // into the current city ordering.
  using permutation_t = std::vector<unsigned int>;

  Cities();
  ~Cities();

  // [
  // friend functions defined outside class scope, but can access private members
  // allow for the reading  / filling of a Cities object from a stream
  friend std::istream& operator>>(std::istream& is, Cities& cities)
  {
    int a; int b;
    while (is >> a) {
      is >> b;
      coord_t cityCoords = std::make_pair(a,b);
      cities.cities_.push_back(cityCoords);
    }
    return is;
  }

  // allow for the outputting of a Cities object to a stream
  friend std::ostream& operator<<(std::ostream& out, Cities& cities)
  {
    for (long unsigned int i=0; i < cities.cities_.size(); i++) {
      out << cities.cities_[i].first << " " << cities.cities_[i].second << "\n";
    }
     return out;
  }
  // ]

  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;

  // Generates and returns new permutation of all the numbers from 0 to len-1
  // (with no skipped or repeated indices)
  permutation_t random_permutation(unsigned int len);

  // Return how many cities there are
  int get_cities_size();

 private:
  coord_t coords_;
  cities_t cities_;
  permutation_t perm_;
};
