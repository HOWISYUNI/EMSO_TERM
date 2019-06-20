#mkdir ./bin
rm -r bin
mkdir bin

#lib compile
##network lib compile
arm-linux-gnueabi-gcc -c ./../KSF_NET/ksf_net_lib.c
##controller lib compile
arm-linux-gnueabi-gcc -c ./lib/ACTUATOR/actuator_lib.c

#app compile
arm-linux-gnueabi-gcc -I. -o ./bin/actuator_ctl ./App/actuator_controller.c ksf_net_lib.o actuator_lib.o

#delete .o
rm ksf_net_lib.o actuator_lib.o

#scp
scp ./App/snapshot.sh ./bin/actuator_ctl pi@10.10.10.16:~/ku_smart_farm/
