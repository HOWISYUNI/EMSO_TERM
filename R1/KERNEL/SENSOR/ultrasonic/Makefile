KDIR := ~/linux-rpi
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := ultrasonic.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules

copy:
	scp ultrasonic.ko mknod.sh pi@10.10.10.13:~/TP/ultrasonic

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
