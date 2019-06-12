#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

/*
#define START_NUM 0x80
#define IOCTL_NUM1 START_NUM+1
#define IOCTL_NUM2 START_NUM+2
#define IOCTL_NUM3 START_NUM+3
#define IOCTL_NUM4 START_NUM+4
#define IOCTL_NUM5 START_NUM+5

#define SIMPLE_IOCTL_NUM 'z'
#define SOIL_SAVE _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM1, unsigned long *)
#define DHT_SAVE _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM2, unsigned long *)
#define LIGHT_SAVE _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM3, unsigned long *)	
#define ULSN_SAVE _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM4, unsigned long *)	
#define TEMP_SAVE _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM5, unsigned long *)
*/

int save_data(char type, char* data);
char* refine_data(char type, char cmd);
