KDIR := ~/linux-rpi
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := motor.o water_pump.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules

copy:
	scp motor.ko water_pump.ko motor_mknod.sh water_pump_mknod.sh pi@10.10.10.13:~/ku_smart_farm/modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
