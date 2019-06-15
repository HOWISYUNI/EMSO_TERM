#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include "../../devices.h"
#define TRUE 1
#define FALSE 0

static long pir_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
