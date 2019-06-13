/* sensor library header */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		/* close */
#include <sys/fcntl.h>
#include <sys/ioctl.h>

int read_light_sensor();

int read_soil_sensor();
int read_dht11_sensor();

int open_pir_sensor();
void close_pir_sensor(int dev);

int open_ultrasonic_sensor();
void close_ultrasonic_sensor(int dev);

