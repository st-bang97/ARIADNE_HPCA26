bash Install_ARIADNE.sh

rmmod nvidia_uvm
insmod ./ARIADNE/kernel-open/nvidia-uvm.ko uvm_perf_fhp=0
sleep 1
bash run_bench.sh no_PL

sleep 1

rmmod nvidia_uvm
insmod ./ARIADNE/kernel-open/nvidia-uvm.ko uvm_perf_fhp=0 uvm_perf_SDaware=0
sleep 1
bash run_bench.sh no_PL_SD

