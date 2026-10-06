#!/bin/bash

benchmarks=("2DCONV" "ATAX" "BICG" "GEMM" "hellinger" "nw" "bfs" "GESUMMV" "MVT" "XSBench")
footprints=(4136 4096 4096 4106 4106 4096 4096 4136 4096 4096)
oversub=(0 30 75 200)

pwd0=$(pwd)
echo ${pwd0}
echo ""

cp penguin-suv.h penguin.h
for ((idx=0; idx<${#benchmarks[@]}; ++idx)); do
    benchmark=${benchmarks[idx]}
    footprint=${footprints[idx]} 
    echo "Processing $benchmark $footprint"
    for os in ${oversub[@]}; do
        bash new_set_mem_resv.sh $benchmark $footprint $os
        #bash new_set_mem_resv.sh $benchmark 4096 $os
        cd ${pwd0}
        cd benchmark
        cd $benchmark
        echo $(pwd)
        echo "suv.${os}.out"
        rm suv.${os}.out
        bash run_passes.sh $SUVHOME $SUVHOME/llvm/ suv.${os}.out
        cd ${pwd0}
        echo ""
    done
done
