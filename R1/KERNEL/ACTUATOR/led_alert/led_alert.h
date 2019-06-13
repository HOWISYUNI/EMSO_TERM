#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/timer.h>

#define LED_ALERT_IOCTL 0x20
#define LED_ALERT_IOCTL_NUM1 LED_ALERT_IOCTL+1
#define LED_ALERT_IOCTL_NUM2 LED_ALERT_IOCTL+2
#define LED_ALERT_IOCTL_NUM3 LED_ALERT_IOCTL+3
#define LED_ALERT_IOCTL_NUM 'b'

#define TURN_ON_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM1, unsigned long *)
#define TURN_OFF_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM2, unsigned long *)
#define TIME_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM3, unsigned long *)

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
