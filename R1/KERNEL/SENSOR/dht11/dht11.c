/*
 *20190527 jinho
 *dht11.c
 *
 *
 *
 * */

#include "dht11.h"

MODULE_LICENSE("GPL");

static dev_t dev_num;
static struct cdev *cd_cdev;

static int dht11_data[5] = {0,};

static void dht_read(void){
	int flag=0;
	while(flag==0)
	{
		int last_state = 1;
		int counter = 0;
		int i = 0;
		int j = 0;

		dht11_data[0] = dht11_data[1] = dht11_data[2] = dht11_data[3] = dht11_data[4] = 0;

		gpio_direction_output(DHT, 0);
		gpio_set_value(DHT, 0);
		mdelay(18);
		gpio_set_value(DHT, 1);
		udelay(40);
		gpio_direction_input(DHT);
	
		for(i = 0;i < MAX_TIMING; i++){
			counter = 0;
			while(gpio_get_value(DHT) == last_state){
				counter++;
				udelay(1);
				if(counter == 255)	break;
			
			}
	

			last_state = gpio_get_value(DHT);
	
			if(counter == 255)	break;
		
			if( (i >= 4) && (i%2 == 0) ){
				dht11_data[j/8] <<= 1;
				if(counter > 16)	dht11_data[j/8] |= 1;
		
				j++;
			}
		}

		if( (j >= 40) && (dht11_data[4] == ( (dht11_data[0]+dht11_data[1]+dht11_data[2]+dht11_data[3]) & 0xFF) ) ){
			printk("Humidity:%d.%d Temperature = %d.%dC \n", dht11_data[0], dht11_data[1], dht11_data[2], dht11_data[3]);
			flag=1;
		}else{
			mdelay(200);
		}
	}
	
}

static int dht11_read(struct file *file, char *buf, size_t len, loff_t *lof){
	int ret;
	dht_read();
	printk("Humidity:%d.%d Temperature = %d.%dC \n", dht11_data[0], dht11_data[1], dht11_data[2], dht11_data[3]);
	ret = copy_to_user(buf,&dht11_data[2],sizeof(int));
	
	return 0;
}

static int dht11_open(struct inode *inode, struct file *file){

	return 0;
}

static int dht11_release(struct inode *inode, struct file *file){
	
	return 0;
}

struct file_operations dht11_fops = {
	.open = dht11_open,
	.release = dht11_release,
	.read = dht11_read,
};

static int __init dht11_init(void){

	gpio_request(DHT, "DHT11");

	alloc_chrdev_region(&dev_num, 0, 1, DEV_DHT);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &dht11_fops);
	cdev_add(cd_cdev, dev_num, 1);
	
	return 0;
}

static void __exit dht11_exit(void){
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);
	gpio_set_value(DHT, 0);
	gpio_free(DHT);
}

module_init(dht11_init);
module_exit(dht11_exit);
