#include "sprinkler.h"

MODULE_LICENSE("GPL");

static struct timer_list timer_w;
static dev_t dev_num;
static struct cdev *cd_cdev;

static void timer_func(unsigned long data){
    gpio_set_value(WATERPUMP_A, 1);
	gpio_set_value(WATERPUMP_B, 0);
}

void pump_on(void){
	gpio_set_value(WATERPUMP_A, 1);
	gpio_set_value(WATERPUMP_B, 0);

}

void pump_off(void){
	gpio_set_value(WATERPUMP_A, 1);
	gpio_set_value(WATERPUMP_B, 1);

}

static long water_pump(struct file *file, unsigned int cmd, unsigned long arg){

	switch(cmd){
		case PUMP_ON:
		    pump_on();
		    break;
		case PUMP_OFF:
		    pump_off();
		    break;
		case PUMP_TIMER:
		    del_timer(&timer_w);
		    timer_w.function = timer_func;
		    timer_w.data = 1L;
		    timer_w.expires = jiffies + (arg*HZ);
		    pump_on();
		    add_timer(&timer_w);
		    break;
		default:
			return -1;
	}

	return 0;
}

struct file_operations water_pump_fops = {
	.unlocked_ioctl = water_pump
};


static int __init water_pump_init(void){
    /* timer init */
    init_timer(&timer_w);
    /* gpio init */
	gpio_request_one(WATERPUMP_A, GPIOF_OUT_INIT_HIGH, "PUMP_A");
	gpio_request_one(WATERPUMP_B, GPIOF_OUT_INIT_HIGH, "PUMP_B");
	pump_off();
    /* cdev init */
	alloc_chrdev_region(&dev_num, 0, 1, DEV_WTPMP);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &water_pump_fops);
	cdev_add(cd_cdev, dev_num, 1);
	
	return 0;
}

static void __exit water_pump_exit(void){
    /* timer bye */
    del_timer(&timer_w);

    /* gpio init */
    pump_off();
	gpio_free(WATERPUMP_A);
	gpio_free(WATERPUMP_B);

    /* cdev free */
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
}

module_init(water_pump_init);
module_exit(water_pump_exit);
