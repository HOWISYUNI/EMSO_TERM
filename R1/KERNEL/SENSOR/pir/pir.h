#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>

/* PIR */
#define PIR_IOCTL 0x60
#define PIR_IOCTL_NUM1 PIR_IOCTL+1

#define PIR_IOCTL_NUM 'p'
#define DETECT_WAIT _IOWR(PIR_IOCTL_NUM, PIR_IOCTL_NUM1, unsigned long *)


#define SENSOR 17
#define DEV_PIR "pir"

#define TRUE 1
#define FALSE 0

static long pir_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
