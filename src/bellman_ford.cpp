#include "bellman_ford.hpp"

#include <stdexcept>

std::vector<std::vector<int>> bellmanFordAllPairs(const Graph& graph) {
    int V = graph.getNumVertices();
    const auto& edges = graph.getEdgeList();
    std::vector<std::vector<int>> distanceMatrix(V, std::vector<int>(V, INF));

    // Ejecutamos Bellman-Ford tomando cada nodo 's' como origen
    for (int s = 0; s < V; ++s) {
        distanceMatrix[s][s] = 0;

        // Relajación de aristas V-1 veces
        for (int i = 1; i <= V - 1; ++i) {
            for (const auto& edge : edges) {
                int u = edge.u;
                int v = edge.v;
                int w = edge.weight;

                if (distanceMatrix[s][u] != INF &&
                    distanceMatrix[s][u] + w < distanceMatrix[s][v]) {
                    distanceMatrix[s][v] = distanceMatrix[s][u] + w;
                }
            }
        }
        // Pasada final, si podemos seguir relajando, hay un ciclo negativo.
        // Falta arreglar
        for (const auto& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int w = edge.weight;

            if (distanceMatrix[s][u] != INF &&
                distanceMatrix[s][u] + w < distanceMatrix[s][v]) {
                throw std::runtime_error(
                    "Error: El grafo contiene un ciclo de peso negativo "
                    "accesible desde el nodo origen.");
            }
        }
    }
    return distanceMatrix;
}