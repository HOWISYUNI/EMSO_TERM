#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/cdev.h>

#define DEV_NAME "ultrasonic"

#define TRIG 6
#define ECHO 26	

/* function : buzzer on
 * parameter : N/A
 * return : file desciptor */
static irqreturn_t ultrasonic_isr(int irq, void* dev_id);


