KERNELDIR := ~/linux-rpi/
ARM := ARCH=arm CROSS_COMPILE=/usr/bin/arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := soil_sensor.o

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) $(ARM) modules

copy:


clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) $(ARM) clean
