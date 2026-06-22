#!/bin/bash

# Compilamos el ejecutable si no existe o ha cambiado
echo "Compilando procesador de datasets reales"
g++ -std=c++17 -O3 src/graph.cpp src/floyd_warshall.cpp experimentos/data.cpp -o experimentos/data

# Definimos las rutas absolutas o relativas al script
RAW_DIR="data/raw"
OUT_DIR="data/output"

# Aseguramos que la carpeta de salida exista
mkdir -p "$OUT_DIR"

echo "================================================="
echo " INICIANDO PROCESAMIENTO DE DATASETS REALES"
echo "================================================="

# Array con los nombres de los archivos que debes procesar
DATASETS=(
    "bio-SC-TS.edges"
    "power-685-bus.mtx"
)

# Iteramos sobre cada dataset
for file in "${DATASETS[@]}"; do
    # Ruta completa del archivo de entrada
    INPUT_PATH="$RAW_DIR/$file"
    
    # Creamos el nombre del archivo de salida (cambiamos .mtx o .edges por .csv) y lo guardamos en la carpeta output
    OUTPUT_FILE="${file%.*}.csv"
    OUTPUT_PATH="$OUT_DIR/$OUTPUT_FILE"
    
    if [ -f "$INPUT_PATH" ]; then
        echo "Procesando: $file"
        ./experimentos/data "$INPUT_PATH" "$OUTPUT_PATH"
    else
        echo "No se encontró el dataset: $INPUT_PATH"
    fi
done

echo "================================================="
echo " PROCESAMIENTO FINALIZADO. Resultados en $OUT_DIR/"
echo "================================================="