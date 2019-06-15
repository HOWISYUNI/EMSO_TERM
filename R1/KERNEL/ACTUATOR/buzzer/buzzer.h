#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/cdev.h>

#include "../../devices.h"

/* function : buzzer 
 * parameter : N/A
 * return : 0(success), -1(fail) */
static long buzzer(struct file *file, unsigned int cmd, unsigned long arg);

static void buzzer_do(unsigned long data);
static void buzzer_me(unsigned long data);
static void timer_buzzer(unsigned long data);
