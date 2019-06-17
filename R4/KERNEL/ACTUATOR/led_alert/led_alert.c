/*
 * 20190524 aeomhs
 * led_alert.c
 * open : LED_ALERT on
 * close : LED_ALERt off
 * */

#include "led_alert.h"

MODULE_LICENSE("GPL");

static struct timer_list timer;
static dev_t dev_num;
static struct cdev *cd_cdev;

static void timer_func(unsigned long data){
    printk("led alert down\n");
	gpio_set_value(LED_ALERT, 0);
}

static long led_alert_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
        switch( cmd ){
        case TURN_ON_LEDA:
                printk("turn on led alert\n");
                gpio_set_value(LED_ALERT, 1);
                break;
        case TURN_OFF_LEDA:
                printk("turn off led alert\n");
                gpio_set_value(LED_ALERT, 0);
                break;
        case TIME_LEDA:
                printk("turn on led alert until expire timer : %ld\n", arg);
                del_timer(&timer);
                timer.function = timer_func;
	            timer.data = 1L;
	            timer.expires = jiffies + (arg*HZ);
	            gpio_set_value(LED_ALERT, 1);
	            add_timer(&timer);
                break;
        default:
                return -1;
        }

        return 0;
}


struct file_operations led_alert_fops = {
	.unlocked_ioctl = led_alert_ioctl,
};

static int __init led_alert_init(void){
    /* timer init */
    init_timer(&timer);
    
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
    /* timer bye */
   	del_timer(&timer);
    /* cdev free */
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
    /* gpio free */
    gpio_free(LED_ALERT);
}

module_init(led_alert_init);
module_exit(led_alert_exit);
