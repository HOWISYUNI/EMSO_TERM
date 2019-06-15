#clean
rm -r bin/
mkdir bin/

#lib compile
##Net compile
arm-linux-gnueabi-gcc -c ./lib/KSF_NET/ksf_net_lib.c
##ctl compile
arm-linux-gnueabi-gcc -c ./lib/controllers.c

#app compile
arm-linux-gnueabi-gcc -I. -o ./bin/refine_ctl ./App/refine_controller.c ksf_net_lib.o controllers.o
arm-linux-gnueabi-gcc -I. -o ./bin/storage_ctl ./App/storage_controller.c ksf_net_lib.o controllers.o

#delete .o
rm ksf_net_lib.o controllers.o

#scp
scp ./bin/refine_ctl ./bin/storage_ctl pi@10.10.10.15:~/ku_smart_farm/
