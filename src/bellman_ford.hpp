#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include <vector>

#include "graph.hpp"

// Algoritmo Base: Ejecuta Bellman-Ford V veces (una desde cada nodo origen)
std::vector<std::vector<int>> bellmanFordAllPairs(const Graph& graph);

#endif