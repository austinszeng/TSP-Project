#include "cities.hh"
#include <cassert>

using namespace std;

int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "There should only be one argument.\n";
    return 0;
  }
  std::fstream fin;
  fin.open(argv[1]); // open inputted file for input/ output operations
  assert(fin);
  Cities cities;
  fin >> cities; // input city file data into cities object
  Cities::permutation_t bestPerm = cities.random_permutation(cities.get_cities_size());
  int iterations = 1000000; // Iterate over a fixed number of iterations
  for (auto i = 1; i < iterations; i++) {
    Cities::permutation_t newPerm = cities.random_permutation(cities.get_cities_size()); // generate a new random permutation
    // evaluate the distance to travel the cities along this ordering
    // and compare it to the shortest distance found so far
    if (cities.total_path_distance(newPerm) < cities.total_path_distance(bestPerm)) {
      bestPerm = newPerm;
      cout << i << "  " << cities.total_path_distance(bestPerm) << "\n"; // print iteration number and total distance of the new shortest path
    }
  }
  cities = cities.reorder(bestPerm);
  // Save city ordering to a file called "shortest.tsv".
  auto fout = ofstream("shortest.tsv");
  fout << cities;
  return 0;
}
