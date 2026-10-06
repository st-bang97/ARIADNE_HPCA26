#NVDIA opensource kernel module driver install
cd ./UVM/
#sudo make clean
sudo make modules -j32
sleep 1

sudo rmmod nvidia-uvm
sudo rmmod nvidia-drm
sudo rmmod nvidia-modeset
sudo rmmod nvidia

sleep 1

sudo insmod ./kernel-open/nvidia.ko NVreg_OpenRmEnableUnsupportedGpus=1
sudo insmod ./kernel-open/nvidia-uvm.ko uvm_perf_access_counter_mimc_migration_enable=1

