KDIR := ~/linux-rpi
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := pir.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules

copy:
	scp pir.ko mknod.sh pi@10.10.10.13:~/TP/pir

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
