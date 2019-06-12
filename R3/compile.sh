#lib compile
##Net compile
arm-linux-gnueabi-gcc -c ./lib/KSF_NET/ksf_net_lib.c
##ctl compile
arm-linux-gnueabi-gcc -c ./lib/controllers.c

#app compile
#arm-linux-gnueabi-gcc -I. -o refine_ctl ./App/refine_controller.c ksf_net_lib.o controllers.o
arm-linux-gnueabi-gcc -I. -o storage_ctl ./App/storage_controller.c ksf_net_lib.o controllers.o

#delete .o
rm ksf_net_lib.o controllers.o

#move binary
#mv refine_ctl ./App/
mv storage_ctl ./App/
