/*
 * 20190524 aeomhs
 * led.c
 * open : LED on
 * close : LED off
 * */
#include "led.h"

MODULE_LICENSE("GPL");

static struct timer_list timer;
static dev_t dev_num;
static struct cdev *cd_cdev;

static void timer_func(unsigned long data){
    printk("led down\n");
	gpio_set_value(LED, 0);
}

static long led_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
        switch( cmd ){
        case TURN_ON_LED:
                printk("turn on led\n");
                gpio_set_value(LED, 1);
                break;
        case TURN_OFF_LED:
                printk("turn off led\n");
                gpio_set_value(LED, 0);
                break;
        case TIME_LED:
                printk("turn on led until expire timer : %ld\n", arg);
                del_timer(&timer);
                timer.function = timer_func;
	            timer.data = 1L;
	            timer.expires = jiffies + (arg*HZ);
	            gpio_set_value(LED, 1);
	            add_timer(&timer);
                break;
        default:
                return -1;
        }

        return 0;
}

struct file_operations led_fops = {
	.unlocked_ioctl = led_ioctl,
};

static int __init led_init(void){
    /* timer init */
    init_timer(&timer);

    /* gpio init */
    gpio_request_one(LED, GPIOF_OUT_INIT_LOW, "LED");

    /* cdev init */
    alloc_chrdev_region(&dev_num, 0, 1, DEV_LED);
    cd_cdev = cdev_alloc();
    cdev_init(cd_cdev, &led_fops);
    cdev_add(cd_cdev, dev_num, 1);
	
    return 0;
}

static void __exit led_exit(void){
    /* timer bye */
   	del_timer(&timer);
    /* cdev free */
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
    /* gpio free */
    gpio_free(LED);
    
}

module_init(led_init);
module_exit(led_exit);
