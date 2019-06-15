#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/kthread.h>
#include "../../devices.h"
#define STEPS 8
#define MOTOR_SPEED 1000

/* moter */
void setStep(int pin1, int pin2, int pin3, int pin4);
void forward(int cycle, int delay);
void backward(int cycle, int delay);
void moveDegree(int degree, int delay, int direction);
/* water_pump */
void pump_on(void);
void pump_off(void);

