#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include "../../devices.h"

/* 
 * emergency line control
 * */
static long emg_line_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
