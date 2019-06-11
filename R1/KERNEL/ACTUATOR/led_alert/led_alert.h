#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>

#define DEV_LED_ALERT "led_alert"
#define LED_ALERT 5

/* 
 * function : LED ALERT on
 * parameter : file path, mode
 * return : file descriptor
 * */
static int led_alert_open(struct inode *inode, struct file *file);
/*
 * function : LED ALERT off
 * parameter : file path, mode
 * return : file descriptor
 * */
static int led_alert_release(struct inode *inode, struct file *file);

