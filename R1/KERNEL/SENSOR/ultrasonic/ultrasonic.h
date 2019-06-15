#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEV_NAME "ultrasonic_dev"

#define TRIG 6
#define ECHO 26	


/* function : Start to measure distance
 * parameter : inode, file
 * return : distance */
/* function : When ultrasonic_open function open, it measure distance
 * parameter : irq, dev_id
 * return : IRQ_HANDLED */


