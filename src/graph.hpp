#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

const int INF = 1e9;

struct Edge {
    int u, v;
    int weight;
};

class Graph {
   private:
    int numVertices;
    std::vector<std::vector<int>> adjMatrix;
    std::vector<Edge> edgeList;

   public:
    Graph(int vertices);

    //  Añadir aristas dirigidas
    void addEdge(int u, int v, int weight);

    // Getters
    int getNumVertices() const;
    const std::vector<std::vector<int>>& getAdjMatrix() const;
    const std::vector<Edge>& getEdgeList() const;
};

#endif