#NVDIA opensource kernel module driver install
cd ./ARIADNE/
#sudo make clean
sudo make modules -j32
sleep 1

sudo rmmod nvidia-uvm
sudo rmmod nvidia-drm
sudo rmmod nvidia-modeset
sudo rmmod nvidia

sleep 1

sudo make modules_install
sleep 1
sudo depmod -A

