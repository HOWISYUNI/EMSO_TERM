#lib compile
arm-linux-gnueabi-gcc -c ./lib/device_lib.c

#app compile
arm-linux-gnueabi-gcc -c ./App/sf_subctr.c
arm-linux-gnueabi-gcc -I. -o daemon ./App/daemon.c device_lib.o sf_subctr.o
