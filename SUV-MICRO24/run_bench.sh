#!/bin/bash

# ==============================================================================
# Benchmark Runner Script
#
# Runs a series of GPU benchmarks with different datasets, extracts the
# GPU runtime, and logs the results to a file.
#
# Usage: ./run_benchmarks.sh <label>
#   <label>: A descriptive label (e.g., "prefetch_on") used in the output
#            filename to distinguish this run.
# ==============================================================================

# --- Configuration ---

# Set SUV_HOME to the current working directory to allow native execution
# without hardcoded user paths.
# NOTE: Run this script from the project root (e.g., inside SUV-MICRO24/).
readonly SUV_HOME=$(pwd)

readonly BENCHMARKS=(
    "2DCONV"
    "GESUMMV"
    "ATAX"
    "GEMM"
    "nw"
    "MVT"
    "BICG"
    "XSBench"
    "hellinger"
    "bfs"
)

readonly TEST_LABELS=("nooversub" "130" "175" "300")
readonly TEST_SUFFIXES=("0" "30" "75" "200")


# --- Script Setup ---

# Check if the required command-line argument (the label) was provided.
if [ -z "$1" ]; then
    echo "Error: Missing run label." >&2
    echo "Usage: $0 <label>" >&2
    exit 1
fi
readonly PREFETCH_LABEL=$1

# Set the environment variables required for CUDA and the custom LLVM build.
export PATH="/usr/local/cuda/bin:${SUV_HOME}/llvm/build/bin:${PATH}"
export LD_LIBRARY_PATH="/usr/local/cuda/lib64:${LD_LIBRARY_PATH}"
export SUVHOME="${SUV_HOME}/"

# Define the output directory and log file path.
# Results are now stored in a local ./result directory.
readonly RESULT_DIR="$SUVHOME/../result"
readonly LOG_FILE="${RESULT_DIR}/${PREFETCH_LABEL}"

# Create the result directory if it doesn't exist.
if [ ! -d "${RESULT_DIR}" ]; then
    echo "Creating result directory: ${RESULT_DIR}"
    mkdir -p "${RESULT_DIR}"
fi


# --- Helper Function ---

function run_single_benchmark() {
    local name=$1
    local suffix=$2
    local bench_dir="${SUVHOME}/benchmark/${name}"
    local executable="suv.${suffix}.out"
    local tmp_output_file="${bench_dir}/imsi.txt"

    echo "--> Running benchmark: ${name} (${executable})"

    # Check if benchmark directory exists before trying to run
    if [ ! -d "${bench_dir}" ]; then
        echo "    Error: Directory ${bench_dir} not found."
        echo "${name} FAILED_DIR_NOT_FOUND" >> "${LOG_FILE}"
        return
    fi

    # Ensure the temporary file from a previous run is removed.
    rm -f "${tmp_output_file}"

    # Define specific parameters for certain benchmarks.
    local params=""
    if [ "${name}" == "nw" ]; then
        params="23120 23120"
        echo "    -> Using specific parameters for nw: ${params}"
    fi

    (cd "${bench_dir}" && timeout 6000s "./${executable}" ${params} > "${tmp_output_file}" 2>&1)
    local exit_code=$?

    local result_text
    if [ -f "${tmp_output_file}" ]; then
        result_text=$(grep 'GPU Runtime' "${tmp_output_file}")
    fi

    if [ ${exit_code} -eq 124 ]; then
        result_text="GPU Runtime: FAILED (TIMED OUT after 6000s)"
    elif [ -z "${result_text}" ]; then
        result_text="GPU Runtime: FAILED_OR_NOT_FOUND (Exit Code: ${exit_code})"
    fi

    echo "${name} ${result_text}" >> "${LOG_FILE}"

    echo "    ...Done. Result for ${name} has been logged."
    sleep 4 
}


# --- Main Execution Logic ---

echo "Starting benchmark suite."
echo "Home Directory (SUV_HOME): ${SUV_HOME}"
echo "Results will be saved to:  ${LOG_FILE}"

# Initialize the log file by clearing it.
> "${LOG_FILE}"

# Loop through each test configuration.
for i in "${!TEST_LABELS[@]}"; do
    label="${TEST_LABELS[$i]}"
    suffix="${TEST_SUFFIXES[$i]}"

    echo
    echo "================================================================="
    echo "Starting Test Set: ${label} (using .${suffix}.out executables)"
    echo "================================================================="

    # Write the section header to the log file.
    echo -e "\n${label}" >> "${LOG_FILE}"

    # Run every benchmark for the current configuration.
    for bench_name in "${BENCHMARKS[@]}"; do
        run_single_benchmark "${bench_name}" "${suffix}"
    done
done

echo
echo "Benchmark suite finished successfully."
