/* sensor library header */

#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

int read_light_sensor();
int read_soil_sensor();
void read_dht11_sensor(int dht11_data[]);
int open_pir_sensor();
void close_pir_sensor(int dev);

