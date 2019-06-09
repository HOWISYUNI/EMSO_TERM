#lib compile
#arm-linux-gnueabi-gcc -c ./lib/ACTUATOR/actuator_lib.c
arm-linux-gnueabi-gcc -c ./lib/KSF_NET/ksf_server_lib.c
arm-linux-gnueabi-gcc -c ./lib/KSF_NET/ksf_client_lib.c

#app compile
#arm-linux-gnueabi-gcc -c ./App/sf_subctr.c
#arm-linux-gnueabi-gcc -I. -o daemon ./App/daemon.c actuator_lib.o sf_subctr.o
arm-linux-gnueabi-gcc -I. -o server ./App/ksf_net_server.c ksf_server_lib.o
arm-linux-gnueabi-gcc -I. -o client ./App/ksf_net_client.c ksf_client_lib.o

#delete .o
#rm actuator_lib.o sf_subctr.o
rm ksf_server_lib.o ksf_client_lib.o

#move binary
#mv daemon ./App/
mv server ./App/
mv client ./App/
