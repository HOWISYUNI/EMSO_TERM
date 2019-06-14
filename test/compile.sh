#lib compile
arm-linux-gnueabi-gcc -c ./ksf_net_lib.c

#app compile
arm-linux-gnueabi-gcc -I. -o request ./request.c ksf_net_lib.o

#delete .o
rm ksf_net_lib.o
