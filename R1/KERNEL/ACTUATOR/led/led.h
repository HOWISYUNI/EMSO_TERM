#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>

#define DEV_NAME "led"
#define LED 4

/* 
 * function : LED on
 * parameter : file path, mode
 * return : file descriptor
 * */
static int led_open(struct inode *inode, struct file *file);
/*
 * function : LED off
 * parameter : file path, mode
 * return : file descriptor
 * */
static int led_release(struct inode *inode, struct file *file);

