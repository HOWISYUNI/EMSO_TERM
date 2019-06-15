#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>

#define SENSOR 17
#define DEV_NAME "pir"

static long pir_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
//static int pir_open(struct inode *inode, struct file* file);
//static int pir_release(struct inode *inode, struct file* file);
