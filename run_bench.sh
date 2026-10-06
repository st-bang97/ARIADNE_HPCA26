#!/bin/bash

# ==============================================================================
# HPCA26 Artifact Evaluation - Oversubscription Benchmark Script
# 
# Location: ~/HPCA26_AE_ARIADNE/run_oversub_bench.sh
# Description: Executes benchmarks within the 'benchmarks' directory, using 
#              'hostpin' to adjust Oversubscription levels and measuring 
#              execution time.
# ==============================================================================

# --- Configuration ---

# Check for output filename argument
if [ -z "$1" ]; then
    echo "Error: Output filename argument is missing."
    echo "Usage: $0 <output_filename>"
    exit 1
fi

OUTPUT_FILENAME="$1"

# Current directory (HPCA26_AE_ARIADNE)
BASE_DIR=$(pwd)
BENCH_DIR="${BASE_DIR}/benchmarks"
RESULT_DIR="${BASE_DIR}/results"
HOSTPIN_EXEC="${BENCH_DIR}/hostpin"

# Create result directory if it doesn't exist
if [ ! -d "$RESULT_DIR" ]; then
    mkdir -p "$RESULT_DIR"
fi

# Output file path
OUTPUT_FILE="${RESULT_DIR}/${OUTPUT_FILENAME}"

# List of benchmarks to run
BENCHMARKS=(
    "2DCONV"
    "GESUMMV"
    "ATAX"
    "GEMM"
    "nw"
    "MVT"
    "BICG"
    "hellinger"
    "bfs"
    "XSBench"
)

# Hostpin configuration (Values based on reference file: 4GB / A5000 environment)
# Adjust these values as needed. (Unit: MB or unit accepted by hostpin)
# Find ideal free memory using FB memory usage section of 'nvidia-smi -q',
# Format: "Label:Size"
PIN_CONFIGS=(
    "130:19343"
    "175:20143"
    "300:21128"
)

# --- Functions ---

run_benchmark() {
    local bench_name="$1"
    local bench_path="${BENCH_DIR}/${bench_name}"
    local run_cmd=""

    if [ -f "${bench_path}/run" ]; then
        run_cmd="./run"
    else
        if [ -f "${bench_path}/${bench_name}" ]; then
            run_cmd="./${bench_name}"
        else
            echo "[Error] Cannot find executable for ${bench_name}"
            return
        fi
    fi

    echo "    -> Running ${bench_name}..."
    
    # Move to benchmark directory and execute
    cd "$bench_path" || return

    # Execute and measure time (assumes parsing 'GPU Runtime' via grep)
    # Set timeout to 300 seconds
    local result
    result=$(timeout 600s $run_cmd 2>&1 | grep "GPU Runtime")

    # Handle missing results (Error or Timeout)
    if [ -z "$result" ]; then
        result="Failed or Timeout"
    fi

    # Return to base directory
    cd "$BASE_DIR"

    # Log to result file
    echo "${bench_name} ${result}" >> "$OUTPUT_FILE"
    echo "       Result: ${result}"
}

# --- Main Execution Logic ---

echo "========================================================"
echo " Starting Benchmark Suite"
echo " Results will be saved to: ${OUTPUT_FILE}"
echo "========================================================"

# 1. Run Baseline (No Hostpin)
echo ""
echo "[Phase 1] Baseline (No Oversubscription)"
echo "----------------------------------------"
echo "nooversub" >> "$OUTPUT_FILE"

for bench in "${BENCHMARKS[@]}"; do
    run_benchmark "$bench"
done

# 2. Run with Hostpin (Loop through configurations)
for config in "${PIN_CONFIGS[@]}"; do
    # Parse configuration (Label:Size)
    IFS=':' read -r label size <<< "$config"
    
    echo ""
    echo "[Phase] Oversubscription: ${label}% (Pin Size: ${size})"
    echo "----------------------------------------"
    echo "" >> "$OUTPUT_FILE"
    echo "${label}" >> "$OUTPUT_FILE"

    # Run hostpin in background
    echo "  > Starting hostpin with size ${size}..."
    # Check if hostpin is executable
    if [ -x "$HOSTPIN_EXEC" ]; then
        "$HOSTPIN_EXEC" "$size" &
        HOSTPIN_PID=$!
        
        # Give hostpin a moment to allocate memory
        sleep 5
    else
        echo "[Error] hostpin executable not found or not executable at $HOSTPIN_EXEC"
        continue
    fi

    # Iterate through benchmarks
    for bench in "${BENCHMARKS[@]}"; do
        run_benchmark "$bench"
    done

    # Stop hostpin
    echo "  > Stopping hostpin..."
    kill $HOSTPIN_PID
    wait $HOSTPIN_PID 2>/dev/null
    
    # Ensure process cleanup (kill any residual processes)
    killall hostpin 2>/dev/null
    sleep 3
done

echo ""
echo "========================================================"
echo " All benchmarks completed."
echo " Check results at: ${OUTPUT_FILE}"
echo "========================================================"
