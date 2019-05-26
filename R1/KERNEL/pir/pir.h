#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>

#define SENSOR 17
#define DEV_NAME "pir_sensor_dev"

static int pir_open(struct inode *inode, struct file* file);
static int pir_release(struct inode *inode, struct file* file);
