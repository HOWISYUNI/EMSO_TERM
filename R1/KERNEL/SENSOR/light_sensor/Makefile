KERNELDIR := ~/linux-rpi/
ARM := ARCH=arm CROSS_COMPILE=/usr/bin/arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := light_sensor.o

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) $(ARM) modules

copy:
	scp light_sensor.ko light_mknod.sh pi@10.10.10.13:~/ku_smart_farm/modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) $(ARM) clean
