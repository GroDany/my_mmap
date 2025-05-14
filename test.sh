sudo insmod my_mmap.ko
sudo dmesg | grep "Simple Module"

# DO THE ACTUAL LOGIC HERE

sudo rmmod my_mmap
sudo dmesg | grep "Simple Module"
