#include "waterpump.h"

MODULE_LICENSE("GPL");

static dev_t dev_num;
static struct cdev *cd_cdev;

void pump_on(void){
	printk("pump on");
	/*이게 지금 작동은하는데 물이 어떻게 들어가는지는 잘 모르겠음*/
	gpio_set_value(WATERPUMP_A, 1);
    gpio_set_value(WATERPUMP_B, 0);

}

void pump_off(void){
	printk("pump off");

	gpio_set_value(WATERPUMP_A, 0);
	gpio_set_value(WATERPUMP_B, 0);

}

static int waterpump_open(struct inode *inode, struct file *file){
	pump_on();
	return 0;
}

static int waterpump_release(struct inode *inode, struct file *file){
	pump_off();
	return 0;
}

struct file_operations waterpump_fops = {
	.open = waterpump_open,
	.release = waterpump_release
};

static int __init simple_waterpump_init(void){

	gpio_request_one(WATERPUMP_A, GPIOF_OUT_INIT_LOW, "WATERPUMP_A");
	gpio_request_one(WATERPUMP_B, GPIOF_OUT_INIT_LOW, "WATERPUMP_B");

	printk("init waterpump");

	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &waterpump_fops);
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

static void __exit simple_waterpump_exit(void){

	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);

	gpio_set_value(WATERPUMP_A, 0);
	gpio_set_value(WATERPUMP_B, 0);

	gpio_free(WATERPUMP_A);
	gpio_free(WATERPUMP_B);
}

module_init(simple_waterpump_init);
module_exit(simple_waterpump_exit);
