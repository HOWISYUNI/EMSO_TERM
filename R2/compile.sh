#clean
rm -r bin
mkdir bin

#lib compile
arm-linux-gnueabi-gcc -c ./../KSF_NET/ksf_net_lib.c
arm-linux-gnueabi-gcc -c ./lib/command_controller_lib/led_lib.c
arm-linux-gnueabi-gcc -c ./lib/command_controller_lib/sprinkler_lib.c

#app compile
arm-linux-gnueabi-gcc -I. -o ./bin/command_ctl ./App/command_controller.c ksf_net_lib.o led_lib.o sprinkler_lib.o
arm-linux-gnueabi-gcc -I. -o ./bin/data_ctl ./App/data_controller.c ksf_net_lib.o
arm-linux-gnueabi-gcc -I. -o ./bin/user_interface ./App/user_interface.c ksf_net_lib.o

#delete .o
rm ksf_net_lib.o led_lib.o sprinkler_lib.o

#scp
scp ./bin/command_ctl ./bin/data_ctl ./bin/user_interface pi@10.10.10.14:~/ku_smart_farm/
