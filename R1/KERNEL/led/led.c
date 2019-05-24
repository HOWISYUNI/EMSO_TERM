/*
 * led.c
 * open() : led on
 * close() : led off
 * */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");

#define DEV_NAME "LED"
#define LED 4

static dev_t dev_num;
static struct cdev *cd_cdev;
/* 
 * function : LED on
 * */
static int led_open(struct inode *inode, struct file *file){
	gpio_set_value(LED, 1);
	return 0;
}
/*
 * function : LED off
 * */
static int led_release(struct inode *inode, struct file *file){
	gpio_set_value(LED, 0);
	return 0;
}

struct file_operations led_fops = {
	.open = led_open,
	.release = led_release
};

static int __init led_init(void){
	/* gpio init */
	gpio_request_one(LED, GPIOF_OUT_INIT_LOW, "LED");

	/* cdev init */
	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &led_fops);
	cdev_add(cd_cdev, dev_num, 1);
	
	return 0;
}

static void __exit led_exit(void){
	/* cdev free */
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);
	/* gpio free */
	gpio_free(LED);
}

module_init(led_init);
module_exit(led_exit);
