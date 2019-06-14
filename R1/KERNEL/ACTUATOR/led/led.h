#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/timer.h>

#define LED_IOCTL 0x10
#define LED_IOCTL_NUM1 LED_IOCTL+1
#define LED_IOCTL_NUM2 LED_IOCTL+2
#define LED_IOCTL_NUM3 LED_IOCTL+3

#define LED_IOCTL_NUM 'a'
#define TURN_ON_LED _IOWR(LED_IOCTL_NUM, LED_IOCTL_NUM1, unsigned long *)
#define TURN_OFF_LED _IOWR(LED_IOCTL_NUM, LED_IOCTL_NUM2, unsigned long *)
#define TIME_LED _IOWR(LED_IOCTL_NUM, LED_IOCTL_NUM3, unsigned long *)

#define DEV_LED "led"
#define LED 4

/* 
 * function : ioctl LED
 * parameter : Command ( TURN_ON_LED | TURN_OFF_LED | TIME_LED )
 * return : SUCCESS(0)
 * @TURN_ON_LED : Turn on led
 * @TURN_OFF_LED : Turn off led
 * @TIME_LED : while "arg" second, turn on led
 * */
static long led_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
