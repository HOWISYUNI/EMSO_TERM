#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/timer.h>
#include "../../devices.h"

/* 
 * function : ioctl LED ALERT
 * parameter : Command ( TURN_ON_LED | TURN_OFF_LED | TIME_LED )
 * return : SUCCESS(0)
 * @TURN_ON_LED : Turn on led
 * @TURN_OFF_LED : Turn off led
 * @TIME_LED : while "arg" second, turn on led
 * */
static long led_alert_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
