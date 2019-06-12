#lib compile
arm-linux-gnueabi-gcc -c ./lib/KSF_NET/ksf_net_lib.c
arm-linux-gnueabi-gcc -c ./lib/command_controller_lib/led_lib.c
arm-linux-gnueabi-gcc -c ./lib/command_controller_lib/sprinkler_lib.c

#app compile
arm-linux-gnueabi-gcc -I. -o command_ctl ./App/command_controller.c ksf_net_lib.o led_lib.o sprinkler_lib.o
arm-linux-gnueabi-gcc -I. -o data_ctl ./App/data_controller.c ksf_net_lib.o

#delete .o
rm ksf_net_lib.o led_lib.o sprinkler_lib.o

#move binary
mv command_ctl ./App/
mv data_ctl ./App/
