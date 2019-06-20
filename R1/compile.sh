#mkdir ./bin
rm -r bin
mkdir bin

#lib compile
##network lib compile
arm-linux-gnueabi-gcc -c ./../KSF_NET/ksf_net_lib.c
##controller lib compile
arm-linux-gnueabi-gcc -c ./lib/SENSOR/sensor_lib.c

#app compile
arm-linux-gnueabi-gcc -I. -o ./bin/sensor_ctl ./App/sensor_controller.c ksf_net_lib.o sensor_lib.o

#delete .o
rm ksf_net_lib.o sensor_lib.o

#scp
scp ./bin/sensor_ctl pi@10.10.10.13:~/ku_smart_farm/
