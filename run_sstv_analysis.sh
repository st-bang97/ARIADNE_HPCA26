#!/bin/bash

PINTIME_ARRAY=(50 100 150 200)
SDWEIGHT_ARRAY=(10000 50000 100000 500000)

UVM_MODULE_PATH="./ARIADNE/kernel-open/nvidia-uvm.ko"
BENCHMARK_SCRIPT_PATH="./run_bench.sh"

bash Install_ARIADNE.sh

for pintime_val in "${PINTIME_ARRAY[@]}"; do
    for sdweight_val in "${SDWEIGHT_ARRAY[@]}"; do
        
        echo "==================================================================="
        echo "Starting benchmark with pintime=${pintime_val}, SDweight=${sdweight_val}"
        echo "==================================================================="
        
        echo "Unloading nvidia-uvm module..."
        sudo rmmod nvidia-uvm
        
        sleep 1
        
        echo "Loading nvidia-uvm module with new parameters..."
        sudo insmod ${NVIDIA_MODULE_PATH} NVreg_OpenRmEnableUnsupportedGpus=1
        sudo insmod ${UVM_MODULE_PATH} uvm_dynzero_pintime=${pintime_val} uvm_perf_SD_coeff_evictqueue=${sdweight_val}
        
        sleep 1

        output_filename="sstv_pintime_${pintime_val}_SDweight_${sdweight_val}"
        
        echo "Running benchmark... Output will be saved to: ${output_filename}"
        
        sudo bash ${BENCHMARK_SCRIPT_PATH} ${output_filename}
        
        echo "Benchmark finished for pintime=${pintime_val}, SDweight=${sdweight_val}"
        echo ""
        
    done
done

echo "All benchmarks completed!"
