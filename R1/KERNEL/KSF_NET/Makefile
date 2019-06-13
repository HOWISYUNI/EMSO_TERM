KDIR := ~/linux-rpi
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := ksf_net.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules

copy:
	scp ksf_net.ko pi@10.10.10.13:~/emso/TP/

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
