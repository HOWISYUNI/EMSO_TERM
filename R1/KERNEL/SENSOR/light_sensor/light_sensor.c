#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/uaccess.h>
#include "../../devices.h"
MODULE_LICENSE("GPL");

#define MAX_CLK 12
static dev_t dev_num;
static struct cdev *cd_cdev;
static int light_data;

/*
* light_sensor로 부터 값을 받기 위해 start 신호 등등을 보내는 함수.
*/
void start_mcp(void){
	gpio_direction_output(CE0,0);
	
	gpio_direction_output(SCLK,1);
	udelay(1);
	gpio_direction_output(SCLK,0);
	gpio_direction_output(MOSI,1); 
	udelay(1);
	gpio_direction_output(SCLK,1);
	udelay(1);
	gpio_direction_output(SCLK,0);
	gpio_direction_output(MOSI,1);
	udelay(1);
	gpio_direction_output(SCLK,1);
	udelay(1);
	gpio_direction_output(SCLK,0);
	gpio_direction_output(MOSI,1);
	udelay(1);
	gpio_direction_output(SCLK,1);
	udelay(1);
	gpio_direction_output(SCLK,0);
	gpio_direction_output(MOSI,1);
	udelay(1);
	gpio_direction_output(SCLK,1);
	udelay(1);
	gpio_direction_output(SCLK,0);
	gpio_direction_output(MOSI,1);
	udelay(1);
	gpio_direction_output(SCLK,1);
	udelay(1);
	gpio_direction_output(SCLK,0);
	udelay(1);
	gpio_direction_output(SCLK,1);
	udelay(1);
	gpio_direction_output(SCLK,0);
	udelay(1);
}

void start_light_sensor(void){
	int i=0;
	light_data=0;
	
	gpio_direction_input(MISO);
	start_mcp();
	gpio_set_value(SCLK,1);
	udelay(1);


	for(i=0; i<MAX_CLK; i++){
		gpio_direction_output(SCLK,0);
		udelay(1);
		light_data <<= 1;
		if(gpio_get_value(MISO)==1){
			light_data |= 1;
		}
		gpio_direction_output(SCLK,1);
		udelay(1);
	}
	gpio_direction_output(SCLK,0);
	udelay(1);
	gpio_direction_output(CE0,1);
}
/*
* Parameter : File Description, Buffer(int), lenght(sizeof(int))
* Return : light_data
*/

static int light_sensor_read(struct file *file, char *buf, size_t len, loff_t *lof){
	int ret;
	printk("!!!!!!!!!\n");
	start_light_sensor();
	printk("light value: %u\n",light_data);
	ret = copy_to_user(buf,&light_data,sizeof(int));
	
	return 0;
}

static int light_sensor_open(struct inode *inode, struct file *file){
	

	return 0;
}

static int light_sensor_release(struct inode *inode, struct file *file){



	return 0;
}

struct file_operations light_sensor_fops =
{	
	.open = light_sensor_open,
	.release = light_sensor_release,
	.read = light_sensor_read,

};

static int __init light_sensor_init(void) {

	alloc_chrdev_region(&dev_num, 0, 1, DEV_LIGHT);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &light_sensor_fops);
	cdev_add(cd_cdev, dev_num, 1);

	gpio_request_one(MOSI, GPIOF_OUT_INIT_LOW,"Master Out/ Slave In");
	gpio_request_one(MISO, GPIOF_OUT_INIT_LOW,"Master In/Slave Out");
	gpio_request_one(SCLK, GPIOF_OUT_INIT_LOW,"SCLK");
	gpio_request_one(CE0, GPIOF_OUT_INIT_LOW,"CE0");
	start_light_sensor();
	printk("[init]light value: %u\n",light_data);
	


	return 0;
}
static void __exit light_sensor_exit(void){
	gpio_free(MOSI);
	gpio_free(MISO);
	gpio_free(SCLK);
	gpio_free(CE0);
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);
}

module_init(light_sensor_init);
module_exit(light_sensor_exit);
