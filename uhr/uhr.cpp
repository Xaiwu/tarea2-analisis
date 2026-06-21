/** uhr: generic time performance tester
 * Author: LELE
 *
 * Things to set up:
 * 0. Includes: include all files to be tested,
 * 1. Time unit: in elapsed_time,
 * 2. What to write on time_data,
 * 3. Data type and distribution of RNG,
 * 4. Additive or multiplicative stepping,
 * 5. The experiments: in outer for loop. */

// Compilar con: g++ -O3 -std=c++17 uhr/uhr.cpp -o uhr/uhr

#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "../src/bellman_ford.hpp"
#include "../src/floyd_warshall.hpp"
#include "../src/graph.hpp"
#include "utils.cpp"

// Función auxiliar para generar grafos según el experimento seleccionado
Graph generarGrafoParaMedicion(int n, const std::string& tipo, int seed) {
    Graph g(n);
    std::mt19937 prng(seed);  // Semilla fija
    std::uniform_real_distribution<double> distProb(0.0, 1.0);
    std::uniform_int_distribution<int> distPeso(1, 100);

    if (tipo == "DISPERSOS" || tipo == "DENSOS" || tipo == "PESOS_POS" ||
        tipo == "PESOS_MIX") {
        double p = (tipo == "DISPERSOS") ? 0.1 : 0.9;
        std::uniform_int_distribution<int> distPesoMix(-10, 50);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (distProb(prng) < p) {
                    int peso = (tipo == "PESOS_MIX") ? distPesoMix(prng)
                                                     : distPeso(prng);
                    g.addEdge(i, j, peso);
                }
            }
        }
    } else if (tipo == "ARBOL_BINARIO") {
        // Cada nodo i se conecta a sus "hijos" 2i+1 y 2i+2
        for (int i = 0; i < n; ++i) {
            int leftChild = 2 * i + 1;
            int rightChild = 2 * i + 2;
            if (leftChild < n) g.addEdge(i, leftChild, distPeso(prng));
            if (rightChild < n) g.addEdge(i, rightChild, distPeso(prng));
        }
    } else if (tipo == "BIPARTITO_COMPLETO") {
        // Dividimos los nodos en dos mitades A y B.
        // Todos los de A se dirigen a todos los de B.
        int mitad = n / 2;
        for (int i = 0; i < mitad; ++i) {
            for (int j = mitad; j < n; ++j) {
                g.addEdge(i, j, distPeso(prng));
            }
        }
    }

    return g;
}

int main(int argc, char* argv[]) {
    if (argc < 8) {
        std::cerr << "Uso: " << argv[0]
                  << " <csv> <runs> <low> <up> <BASE|FLOYD> "
                     "<DENSOS|DISPERSOS|PESOS_POS|PESOS_MIX> <parametro_aux>"
                  << std::endl;
        return 1;
    }

    std::int64_t runs, lower, upper;
    validate_input(argc, argv, runs, lower, upper);

    std::string alg_choice = argv[5];  // "BASE" o "FLOYD"
    std::string exp_choice = argv[6];  // Tipo de estructura de la instancia
    int parametro_aux = std::stoi(argv[7]);

    std::ofstream time_data;
    time_data.open(argv[1]);
    time_data << "n,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;

    std::int64_t n, i, executed_runs = 0;
    std::int64_t total_runs =
        runs * (floor(log(upper / double(lower)) / log(2)) + 1);

    std::vector<double> times(runs);
    std::vector<double> q;

    std::cerr << "\033[0;36mRunning tests...\033[0m " << alg_choice << " ["
              << exp_choice << "]" << std::endl;

    for (n = lower; n <= upper; n *= 2) {
        double mean_time = 0;

        // Construir la instancia FUERA de la medición de tiempo cronometrada
        Graph g = generarGrafoParaMedicion(n, exp_choice, parametro_aux);

        for (i = 0; i < runs; i++) {
            display_progress(++executed_runs, total_runs);

            //  INICIO DE MEDICIÓN
            auto begin_time = std::chrono::high_resolution_clock::now();

            if (alg_choice == "BASE") {
                auto res = bellmanFordAllPairs(g);
            } else if (alg_choice == "FLOYD") {
                auto res = floydWarshall(g);
            }

            auto end_time = std::chrono::high_resolution_clock::now();
            // FIN DE MEDICIÓN

            std::chrono::duration<double, std::nano> elapsed =
                end_time - begin_time;
            times[i] = elapsed.count();
            mean_time += times[i];
        }

        // Cálculos estadísticos requeridos por el enunciado
        mean_time /= runs;
        double time_stdev = 0;
        for (i = 0; i < runs; i++) {
            double dev = times[i] - mean_time;
            time_stdev += dev * dev;
        }
        time_stdev = std::sqrt(time_stdev / (runs - 1));

        quartiles(times, q);

        // Guardar al CSV de rendimiento
        time_data << n << "," << mean_time << "," << time_stdev << ",";
        time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << ","
                  << q[4] << std::endl;
    }

    std::cerr << "\033[1;32m\nDone!\033[0m" << std::endl;
    time_data.close();
    return 0;
}