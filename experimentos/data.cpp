#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../src/floyd_warshall.hpp"
#include "../src/graph.hpp"

Graph cargarDatasetReal(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el dataset en " << rutaArchivo
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string linea;
    int maxNodo = 0;
    std::vector<std::pair<int, int>> aristasLeidas;

    while (std::getline(archivo, linea)) {
        // Ignorar líneas de comentarios
        if (linea.empty() || linea[0] == '%' || linea[0] == '#' ||
            linea[0] == 's')
            continue;

        std::stringstream ss(linea);
        int u, v;
        if (ss >> u >> v) {
            aristasLeidas.push_back({u, v});
            maxNodo = std::max({maxNodo, u, v});
        }
    }
    archivo.close();

    // Asumimos indexación basada en 0. Si el nodo máximo es M, necesitamos M +
    // vértices.
    int numeroNodos = maxNodo + 1;
    Graph g(numeroNodos);

    // Insertar aristas con peso unitario (1) por defecto si el grafo no es
    // ponderado
    for (const auto& arista : aristasLeidas) {
        g.addEdge(arista.first, arista.second, 1);
    }

    std::cout << "[Dataset] Cargado. Nodos: " << numeroNodos
              << ", Aristas: " << aristasLeidas.size() << std::endl;
    return g;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0]
                  << " <ruta_dataset_entrada> <ruta_csv_salida>" << std::endl;
        return 1;
    }

    std::string archivoEntrada = argv[1];
    std::string archivoSalida = argv[2];

    std::cout << "Cargando grafo real" << std::endl;
    Graph g = cargarDatasetReal(archivoEntrada);

    std::cout << "Ejecutando Floyd-Warshall sobre el dataset real" << std::endl;
    auto inicio = std::chrono::high_resolution_clock::now();

    // Llamada a tu implementación de Floyd-Warshall
    auto matrizDistancias = floydWarshall(g);

    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempo = fin - inicio;
    std::cout << "Tiempo de ejecucion: " << tiempo.count() << " segundos."
              << std::endl;

    std::ofstream logTiempos(
        "data/output/tiempos_datasets.txt",
        std::ios::app);  // std::ios::app añade al final sin borrar
    if (logTiempos.is_open()) {
        logTiempos << "Dataset: " << archivoEntrada
                   << " | Tiempo: " << tiempo.count() << " segundos.\n";
        logTiempos.close();
    }

    std::cout << "Exportando resultados a " << archivoSalida << "..."
              << std::endl;
    std::ofstream csv(archivoSalida);
    csv << "nodo 1,nodo 2,distancia minima\n";

    int V = g.getNumVertices();
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            // Solo guardamos si existe un camino válido (distancia menor que
            // INF)
            if (matrizDistancias[i][j] != INF) {
                csv << i << "," << j << "," << matrizDistancias[i][j] << "\n";
            }
        }
    }
    csv.close();
    std::cout << "Archivo generado exitosamente." << std::endl;

    return 0;
}