/* sensor library header */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		/* close */
#include <sys/fcntl.h>
#include <sys/ioctl.h>

/* PIR */
#define PIR_IOCTL 0x60
#define PIR_IOCTL_NUM1 PIR_IOCTL+1
#define PIR_IOCTL_NUM 'p'
#define DETECT_WAIT _IOWR(PIR_IOCTL_NUM, PIR_IOCTL_NUM1, unsigned long *)

int read_light_sensor();

int read_soil_sensor();
int read_dht11_sensor();

int open_pir_sensor();
void close_pir_sensor(int dev);

int open_ultrasonic_sensor();
int read_ultrasonic_sensor(int dev);
void close_ultrasonic_sensor(int dev);

int pir_wait();

int emergency_line_up();
int emergency_line_down();

