KDIR := ~/linux-rpi
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := motor.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules

copy:
	scp motor.c mknod.sh pi@10.10.10.13:~/emso/TP/motor

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
