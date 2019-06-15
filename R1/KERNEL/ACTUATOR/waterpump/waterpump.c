#include "sprinkler.h"

MODULE_LICENSE("GPL");

static dev_t dev_num;
static struct cdev *cd_cdev;

/*delay 시간만큼 워터펌프 온*/
void pump_on(int delay){
	printk("pump on");
	/*이게 지금 작동은하는데 물이 어떻게 들어가는지는 잘 모르겠음*/
	gpio_set_value(WATERPUMP_A, 1);
    gpio_set_value(WATERPUMP_B, 0);
	/*작동상태 ing*/
	mdelay(delay);
	/*펌프 오프*/
	gpio_set_value(WATERPUMP_A, 0);
	gpio_set_value(WATERPUMP_B, 0);

}

/*펌프 오프 근데 아마 안쓰일거 같음*/
void pump_off(void){
	printk("pump off");

	gpio_set_value(WATERPUMP_A, 0);
	gpio_set_value(WATERPUMP_B, 0);

}

static int sprinkler_open(struct inode *inode, struct file *file){
	pump_on();
	return 0;
}

static int sprinkler_release(struct inode *inode, struct file *file){
	pump_off();
	return 0;
}

static long sprinkler(struct file *file, unsigned int cmd, unsigned long arg){
		
	switch(cmd){
		case BUZZER_ON:
		    del_timer(&timer);
	    	timer.function = buzzer_me;
        	timer.expires = jiffies + (HZ);
        	add_timer(&timer);
			gpio_set_value(BUZZER, 1);
			break;

		case BUZZER_OFF:
		    del_timer(&timer);
			gpio_set_value(BUZZER, 0);
			break;
			
		case BUZZER_TIME:
		    del_timer(&timer);
		    timer.function = buzzer_me;
        	timer.expires = jiffies + (HZ);
        	add_timer(&timer);
			gpio_set_value(BUZZER, 1);
			
		    del_timer(&end_timer);
			end_timer.function = timer_buzzer;
			end_timer.expires = jiffies + (arg*HZ);
		    add_timer(&end_timer);
		    break;
		    
		default:
			return -1;
	}

	return 0;
}

struct file_operations sprinkler_fops = {
	.open = sprinkler_open,
	.release = sprinkler_release,
	.unlocked_ioctl = sprinkler
};

static int __init sprinkler_init(void){

	gpio_request_one(WATERPUMP_A, GPIOF_OUT_INIT_LOW, "WATERPUMP_A");
	gpio_request_one(WATERPUMP_B, GPIOF_OUT_INIT_LOW, "WATERPUMP_B");

	printk("init waterpump");

	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &sprinkler_fops);
	cdev_add(cd_cdev, dev_num, 1);

	///*test 바로 지우셈
	gpio_set_value(WATERPUMP_A, 1);
    gpio_set_value(WATERPUMP_B, 0);
    mdelay(3000);
    gpio_set_value(WATERPUMP_A, 0);
    gpio_set_value(WATERPUMP_B, 0);
    mdelay(3000);
    gpio_set_value(WATERPUMP_A, 0);
    gpio_set_value(WATERPUMP_B, 1);
    mdelay(3000);
    gpio_set_value(WATERPUMP_A, 0);
    gpio_set_value(WATERPUMP_B, 0);
	//*/

	return 0;
}

static void __exit sprinkler_exit(void){

	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);

	gpio_set_value(WATERPUMP_A, 0);
	gpio_set_value(WATERPUMP_B, 0);

	gpio_free(WATERPUMP_A);
	gpio_free(WATERPUMP_B);
}

module_init(sprinkler_init);
module_exit(sprinkler_exit);
