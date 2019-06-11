/*
 * 20190524 aeomhs
 * led_alert.c
 * open : LED_ALERT on
 * close : LED_ALERt off
 * */

#include "led_alert.h"

MODULE_LICENSE("GPL");

static dev_t dev_num;
static struct cdev *cd_cdev;

static int led_alert_open(struct inode *inode, struct file *file){
    gpio_set_value(LED_ALERT, 1);
    return 0;
}


static int led_alert_release(struct inode *inode, struct file *file){
    gpio_set_value(LED_ALERT, 0);
    return 0;
}

struct file_operations led_alert_fops = {
    .open = led_alert_open,
    .release = led_alert_release
};

static int __init led_alert_init(void){
    /* gpio init */
    gpio_request_one(LED_ALERT, GPIOF_OUT_INIT_LOW, "LED");

    /* cdev init */
    alloc_chrdev_region(&dev_num, 0, 1, DEV_LED_ALERT);
    cd_cdev = cdev_alloc();
    cdev_init(cd_cdev, &led_alert_fops);
    cdev_add(cd_cdev, dev_num, 1);
	
    return 0;
}

static void __exit led_alert_exit(void){
    /* cdev free */
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
    /* gpio free */
    gpio_free(LED_ALERT);
}

module_init(led_alert_init);
module_exit(led_alert_exit);
