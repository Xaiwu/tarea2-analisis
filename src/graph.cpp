#include "graph.hpp"

Graph::Graph(int vertices) : numVertices(vertices) {
    // Inicializamos la matriz con INF en todas partes y 0 en la diagonal
    // principal
    adjMatrix.assign(vertices, std::vector<int>(vertices, INF));
    for (int i = 0; i < vertices; ++i) {
        adjMatrix[i][i] = 0;
    }
}

void Graph::addEdge(int u, int v, int weight) {
    // Grafo dirigido: asignamos el peso en la matriz
    adjMatrix[u][v] = weight;
    // Guardamos también en la lista de aristas para Bellman-Ford
    edgeList.push_back({u, v, weight});
}

int Graph::getNumVertices() const { return numVertices; }

const std::vector<std::vector<int>>& Graph::getAdjMatrix() const {
    return adjMatrix;
}

const std::vector<Edge>& Graph::getEdgeList() const { return edgeList; }