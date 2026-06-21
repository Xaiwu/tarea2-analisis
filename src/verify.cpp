#include <iomanip>
#include <iostream>

#include "bellman_ford.hpp"
#include "floyd_warshall.hpp"
#include "graph.hpp"

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    int V = matrix.size();
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (matrix[i][j] == INF)
                std::cout << std::setw(5) << "INF";
            else
                std::cout << std::setw(5) << matrix[i][j];
        }
        std::cout << "\n";
    }
}

int main() {
    // grafo dirigido de 4 nodos
    Graph g(4);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 3, 7);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 0, 5);
    g.addEdge(3, 2, 4);

    std::cout << " Ejecutando Algoritmo Base (V * Bellman-Ford) \n";
    auto resBase = bellmanFordAllPairs(g);
    printMatrix(resBase);

    std::cout << "\n Ejecutando Algoritmo de Floyd-Warshall \n";
    auto resFloyd = floydWarshall(g);
    printMatrix(resFloyd);

    // Verificación
    if (resBase == resFloyd) {
        std::cout << "\nAmbas implementaciones retornan el mismo"
                     "resultado\n";
    } else {
        std::cout << "\n Las matrices difieren. Revisa las condiciones "
                     "límite.\n";
    }

    return 0;
}