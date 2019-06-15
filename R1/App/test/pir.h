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
