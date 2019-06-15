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

#define DEV_MOTOR "motor"
#define DEV_WTPMP "water_pump"

#define MOTOR_A 6
#define MOTOR_B 13
#define MOTOR_C 19
#define MOTOR_D 26
#define WATERPUMP_A	12
#define WATERPUMP_B	13

#define STEPS 8
#define MOTOR_SPEED 1000

#define SPRNKLER 0x10
#define SPRNKLER_NUM1 SPRNKLER+1
#define SPRNKLER_NUM2 SPRNKLER+2
#define SPRNKLER_NUM3 SPRNKLER+3
#define SPRNKLER_NUM4 SPRNKLER+4
#define SPRNKLER_NUM5 SPRNKLER+5
#define SPRNKLER_NUM6 SPRNKLER+6

#define SPRNKLER_NUM 'k'
#define MOTOR_ON _IOWR(SPRNKLER_NUM, SPRNKLER_NUM1, unsigned long *)
#define MOTOR_OFF _IOWR(SPRNKLER_NUM, SPRNKLER_NUM2, unsigned long *)
#define MOTOR_TIMER _IOWR(SPRNKLER_NUM, SPRNKLER_NUM3, unsigned long *)
#define PUMP_ON _IOWR(SPRNKLER_NUM, SPRNKLER_NUM4, unsigned long *)
#define PUMP_OFF _IOWR(SPRNKLER_NUM, SPRNKLER_NUM5, unsigned long *)
#define PUMP_TIMER _IOWR(SPRNKLER_NUM, SPRNKLER_NUM6, unsigned long *)

/* moter */
void setStep(int pin1, int pin2, int pin3, int pin4);
void forward(int cycle, int delay);
void backward(int cycle, int delay);
void moveDegree(int degree, int delay, int direction);
/* water_pump */
void pump_on(void);
void pump_off(void);

