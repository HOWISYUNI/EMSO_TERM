KDIR := ~/linux-rpi
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := emergency_line.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules

copy:
	scp emergency_line.ko emergency_line_mknod.sh pi@10.10.10.13:~/ku_smart_farm/modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
