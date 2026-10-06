export PATH=/usr/local/cuda/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH

cd ./SUV-MICRO24
source startup.sh
echo $SUVHOME
sleep 1
bash llvm_setup.sh

cd $SUVHOME
#bash compile.sh
bash driver_change.sh 0 64k 256
bash run_bench.sh SUV
