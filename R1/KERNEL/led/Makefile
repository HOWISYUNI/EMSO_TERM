KDIR := ~/linux-rpi
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := led.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules

copy:
	scp led.ko mknod.sh pi@10.10.10.13:~/emso/TP/led

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
