#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/cdev.h>

#define DEV_NAME "waterpump"

#define WATERPUMP_A	12
#define WATERPUMP_B	13


