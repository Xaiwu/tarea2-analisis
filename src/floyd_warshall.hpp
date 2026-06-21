#ifndef FLOY_WARSHALL_HPP
#define FLOY_WARSHALL_HPP

#include <vector>

#include "graph.hpp"

// Algoritmo de Floyd-Warshall
std::vector<std::vector<int>> floydWarshall(const Graph& graph);

#endif