#include "floyd_warshall.hpp"

std::vector<std::vector<int>> floydWarshall(const Graph& graph) {
    int V = graph.getNumVertices();
    // Copiamos la matriz de adyacencia inicial del grafo como base de la PD
    std::vector<std::vector<int>> dist = graph.getAdjMatrix();

    // k es el nodo intermedio en el camino
    for (int k = 0; k < V; ++k) {
        // i es el nodo origen
        for (int i = 0; i < V; ++i) {
            // j es el nodo destino
            for (int j = 0; j < V; ++j) {
                // Subestructura óptima: evaluamos si pasar por 'k' ofrece un
                // camino más corto
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    return dist;
}