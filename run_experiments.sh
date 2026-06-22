#!/bin/bash

echo "Compilando la suite de experimentos..."
g++ -std=c++17 -O3 src/graph.cpp src/bellman_ford.cpp src/floyd_warshall.cpp uhr/uhr.cpp -o uhr/uhr

# Variables de configuración
RUNS=32
LOWER=125
UPPER=1000
PARAM=42 # Semilla fija para reproducibilidad total

# Crear directorio de salida si no existe
mkdir -p data/output

echo "================================================="
echo " INICIANDO BATERÍA DE EXPERIMENTOS TAREA 2"
echo " Nodos: $LOWER a $UPPER | Ejecuciones: $RUNS"
echo "================================================="

# Experimento 1: Variando Densidad (Grafos Densos)
echo "Ejecutando Experimento 1: Grafos Densos (p=0.9)"
./uhr/uhr data/output/base_densos.csv $RUNS $LOWER $UPPER BASE DENSOS $PARAM
./uhr/uhr data/output/floyd_densos.csv $RUNS $LOWER $UPPER FLOYD DENSOS $PARAM

# Experimento 2: Variando Densidad (Grafos Dispersos)
echo "Ejecutando Experimento 2: Grafos Dispersos (p=0.1)"
./uhr/uhr data/output/base_dispersos.csv $RUNS $LOWER $UPPER BASE DISPERSOS $PARAM
./uhr/uhr data/output/floyd_dispersos.csv $RUNS $LOWER $UPPER FLOYD DISPERSOS $PARAM

# Experimento 3: Topología Extrema (Árbol Binario)
echo "Ejecutando Experimento 3: Árbol Binario (DAG estructurado)"
./uhr/uhr data/output/base_arbol.csv $RUNS $LOWER $UPPER BASE ARBOL_BINARIO $PARAM
./uhr/uhr data/output/floyd_arbol.csv $RUNS $LOWER $UPPER FLOYD ARBOL_BINARIO $PARAM

# Experimento 4: Topología Extrema (Bipartito Completo)
echo "Ejecutando Experimento 4: Bipartito Completo"
./uhr/uhr data/output/base_bipartito.csv $RUNS $LOWER $UPPER BASE BIPARTITO_COMPLETO $PARAM
./uhr/uhr data/output/floyd_bipartito.csv $RUNS $LOWER $UPPER FLOYD BIPARTITO_COMPLETO $PARAM

# Experimento 5: Variando Pesos (Pesos Mixtos con negativos)
echo "Ejecutando Experimento 5: Aleatorios con Pesos Mixtos"
./uhr/uhr data/output/base_mixtos.csv $RUNS $LOWER $UPPER BASE PESOS_MIX $PARAM
./uhr/uhr data/output/floyd_mixtos.csv $RUNS $LOWER $UPPER FLOYD PESOS_MIX $PARAM

echo "================================================="
echo " EXPERIMENTOS FINALIZADOS. Resultados en data/output/"
echo "================================================="