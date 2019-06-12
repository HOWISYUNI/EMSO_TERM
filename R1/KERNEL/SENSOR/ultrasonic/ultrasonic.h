#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/cdev.h>

#define DEV_NAME "ultrasonic"

#define TRIG 6
#define ECHO 26	

/* function : Start to measure distance
 * parameter : inode, file
 * return : distance */
static int ultrasonic_open(struct inode *inode, struct file *file);
static int ultrasonic_release(struct inode *inode, struct file *file);
static int ultrasonic_read(struct file *file, char *buf, size_t len, loff_t *lof);
/* function : When ultrasonic_open function open, it measure distance
 * parameter : irq, dev_id
 * return : IRQ_HANDLED */
static irqreturn_t ultrasonic_isr(int irq, void* dev_id);


