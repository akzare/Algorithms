/*
 * @file   TspBruteForce.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   11 July 2020
 * @version 0.1
 * @brief   This file shows you how to solve the traveling salesman problem using a brute force approach.
 * Since the time complexity is on the order of O(n!) this method is not convenient for n > 12
 *
 * Time Complexity: O(n!)
 */

#ifndef D_GRAPH_TSPBF_H
#define D_GRAPH_TSPBF_H

#include <vector>
#include <deque>
#include <list>
#include <set>   // set and multiset
#include <map>   // map and multimap
#include <unordered_set>  // unordered set/multiset
#include <unordered_map>  // unordered map/multimap
#include <iterator>
#include <algorithm>
#include <numeric>    // some numeric algorithm
#include <functional>
#include <stack>

#include <sstream>
#include <memory>
#include <iostream>
#include <limits>
#include <cassert>

namespace dsa {

namespace TspBruteForce {

const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();

double computeTourCost(const std::vector<int>& tour, const std::vector<std::vector<double> >& matrix) {

  double cost = 0;

  // Compute the cost of going to each city
  for (unsigned i = 1; i < matrix[0].size(); i++) {
    int from = tour[i - 1];
    int to = tour[i];
    cost += matrix[from][to];
  }

  // Compute the cost to return to the starting city
  int last = tour[matrix[0].size() - 1];
  int first = tour[0];
  return cost + matrix[last][first];
}



int getFirst(const std::vector<int>& sequence) {
  for (int i = sequence.size() - 2; i >= 0; --i) if (sequence[i] < sequence[i + 1]) return i;
  return -1;
}

void swap(std::vector<int>& sequence, int i, int j) {
  int tmp = sequence[i];
  sequence[i] = sequence[j];
  sequence[j] = tmp;
}



// Generates the next ordered permutation in-place (skips repeated permutations).
// Calling this when the array is already at the highest permutation returns false.
// Recommended usage is to start with the smallest permutations and use a do while
// loop to generate each successive permutations (see main for example).
bool nextPermutation(std::vector<int>& sequence) {
  int first = getFirst(sequence);
  if (first == -1) return false;
  int toSwap = sequence.size() - 1;
  while (sequence[first] >= sequence[toSwap]) --toSwap;
  swap(sequence, first++, toSwap);
  toSwap = sequence.size() - 1;
  while (first < toSwap) swap(sequence, first++, toSwap--);
  return true;
}



// Given an nxn complete graph represented as an adjacency
// matrix this method finds the best tour that visits all
// the nodes while minimizing the overall visit cost.
std::vector<int> tsp(const std::vector<std::vector<double>>& matrix) {

    int n = matrix[0].size();
    std::vector<int> permutation(n);
    for (int i = 0; i < n; i++) permutation.at(i) = i;

    std::vector<int> bestTour(permutation.size());//(permutation);
    std::copy(permutation.begin(), permutation.end(), bestTour.begin());

    double bestTourCost = POSITIVE_INFINITY;

    // Try all n! tours
    do {
      double tourCost = computeTourCost(permutation, matrix);

      if (tourCost < bestTourCost) {
        bestTourCost = tourCost;
        std::copy(permutation.begin(), permutation.end(), bestTour.begin());
      }

    } while (nextPermutation(permutation));

    return bestTour;
}

} // namespace TspBruteForce


// Example usage of TSP Brute Force
int TspBF_test()
{
  std::cout << "Graph Traveling Salesman Problem(TSP): Solving with Brute Force" << std::endl;

  int n = 10;
  std::vector<std::vector<double> > matrix(n , std::vector<double> (n, 100));

  // Construct an optimal tour
  int edgeCost = 5;
  std::vector<int> optimalTour{2, 7, 6, 1, 9, 8, 5, 3, 4, 0, 2};
  for (unsigned i = 1; i < optimalTour.size(); i++)
    matrix[optimalTour[i - 1]][optimalTour[i]] = edgeCost;

  for (unsigned i = 0; i < matrix[0].size(); i++)
     for (unsigned j = 0; j < matrix[0].size(); j++)

        // Prints ' ' if j != n-1 else prints '\n'
        std::cout << matrix[i][j] << " \n"[j == matrix[0].size()-1];
/*
100 100 5 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 5
100 100 100 100 100 100 100 5 100 100
100 100 100 100 5 100 100 100 100 100b
5 100 100 100 100 100 100 100 100 100
100 100 100 5 100 100 100 100 100 100
100 5 100 100 100 100 100 100 100 100
100 100 100 100 100 100 5 100 100 100
100 100 100 100 100 5 100 100 100 100
100 100 100 100 100 100 100 100 5 100
*/


  std::vector<int> bestTour = TspBruteForce::tsp(matrix);
  std::stringstream str;
  str << "The best tour is: [";
  for (auto node: bestTour) {
    str << "-> ";
    str << node;
  }
  str << "]";
  std::cout << str.str() << std::endl;
// The best tour is: [-> 0-> 2-> 7-> 6-> 1-> 9-> 8-> 5-> 3-> 4]

  double tourCost = TspBruteForce::computeTourCost(bestTour, matrix);
  std::cout << "Tour cost: " << tourCost << std::endl;
// Tour cost: 50
  return 0;
}

} // namespace dsa

#endif /* D_GRAPH_TSPBF_H */
