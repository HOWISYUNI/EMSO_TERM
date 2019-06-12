#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/timer.h>

#define IOCTL_START_NUM 0x80
#define IOCTL_NUM1 IOCTL_START_NUM+1
#define IOCTL_NUM2 IOCTL_START_NUM+2
#define IOCTL_NUM3 IOCTL_START_NUM+3

#define LED_IOCTL_NUM 'z'
#define TURN_ON_LED _IOWR(LED_IOCTL_NUM, IOCTL_NUM1, unsigned long *)
#define TURN_OFF_LED _IOWR(LED_IOCTL_NUM, IOCTL_NUM2, unsigned long *)
#define TIME_LED _IOWR(LED_IOCTL_NUM, IOCTL_NUM3, unsigned long *)

#define DEV_LED_ALERT "led_alert"
#define LED_ALERT 5

/* 
 * function : ioctl LED ALERT
 * parameter : Command ( TURN_ON_LED | TURN_OFF_LED | TIME_LED )
 * return : SUCCESS(0)
 * @TURN_ON_LED : Turn on led
 * @TURN_OFF_LED : Turn off led
 * @TIME_LED : while "arg" second, turn on led
 * */
static long led_alert_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
