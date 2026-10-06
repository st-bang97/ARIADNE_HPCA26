#!/bin/bash

WORKLOADS=("2DCONV" "ATAX" "bfs" "BICG" "GEMM" "GESUMMV" "hellinger" "MVT" "nw" "XSBench")

BASE_DIR=$(pwd)

echo "Starting compilation for all workloads..."

for workload in "${WORKLOADS[@]}"; do
    if [ -d "$workload" ]; then
        echo "=========================================="
        echo "Processing directory: $workload"
        echo "=========================================="
        
        cd "$workload" || exit

        case "$workload" in
            "bfs")
                echo "[BFS] Compiling main.cu..."
                nvcc main.cu -o bfs
		chmod +x run

                if [ -d "inputgen" ]; then
                    echo "[BFS] Building inputgen..."
                    cd inputgen
                    make
                    cd .. 
                else
                    echo "[Error] 'inputgen' directory not found inside bfs."
                fi

                if [ -f "24M_gen_dataset.sh" ]; then
                    echo "[BFS] Running 24M_gen_dataset.sh..."
                    chmod +x 24M_gen_dataset.sh
                    ./24M_gen_dataset.sh
                else
                    echo "[Error] '24M_gen_dataset.sh' not found inside bfs."
                fi
                ;;

            "hellinger")
                echo "[Hellinger] Compiling main.cu..."
                nvcc main.cu -o hellinger
		chmod +x run
                ;;

            *)
		chmod +x run
                if [ -f "Makefile" ] || [ -f "makefile" ]; then
                    echo "[$workload] Running make..."
                    make
                else
                    echo "[Warning] No Makefile found in $workload."
                fi
                ;;
        esac

        cd "$BASE_DIR"
        echo ""
    else
        echo "[Warning] Directory '$workload' does not exist. Skipping."
    fi
done

cd "$BASE_DIR"
nvcc hostpin.cu -o hostpin

echo "All tasks completed."
