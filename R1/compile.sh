#mkdir ./bin
rm -r bin
mkdir bin

#lib compile
arm-linux-gnueabi-gcc -c ./lib/KSF_NET/ksf_net_lib.c

#app compile
arm-linux-gnueabi-gcc -I. -o server ./App/examples/ksf_net_server.c ksf_net_lib.o
arm-linux-gnueabi-gcc -I. -o client ./App/examples/ksf_net_client.c ksf_net_lib.o

#delete .o
rm ksf_net_lib.o

scp server client pi@10.10.10.15:~/emso/TP
rm server client
