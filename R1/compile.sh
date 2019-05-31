#lib compile
arm-linux-gnueabi-gcc -c ./lib/ACTUATOR/actuator_lib.c

#app compile
arm-linux-gnueabi-gcc -c ./App/sf_subctr.c
arm-linux-gnueabi-gcc -I. -o daemon ./App/daemon.c actuator_lib.o sf_subctr.o

#delete .o
rm actuator_lib.o sf_subctr.o

#move binary
mv daemon ./App/
