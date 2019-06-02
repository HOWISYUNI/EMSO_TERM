#include "buzzer.h"

MODULE_LICENSE("GPL");

static dev_t dev_num;
static struct cdev *cd_cdev;
spinlock_t var_lock;

int notes[] = {1911, 1516};	//도, 미
int i;

/* 부저가 여러 개가 되면 ioctl로 분리하자! */
int buzzer_open(struct inode *inode, struct file *file){
	i = 0;
	int j = 0;

	while(i == 0){
		/* 미 */
		for(j = 0; j < 100; j++){
			gpio_set_value(BUZZER1, 1);
			udelay(notes[1]);
			gpio_set_value(BUZZER1, 0);
			udelay(notes[1]);
		}

		/* 도 */
		for(j = 0; j< 100; j++){
			gpio_set_value(BUZZER1, 1);
			udelay(notes[0]);
			gpio_set_value(BUZZER1, 0);
			udelay(notes[0]);
		}
	}
	
	return 0;
}

int buzzer_release(struct inode *inode, struct file *file){
	spin_lock(&var_lock);
	i = 1;
	spin_unlock(&var_lock);    

	return 0;
}

struct file_operations led_fops = {
    .open = buzzer_open,
    .release = buzzer_release
};

static int __init buzzer_init(void){

	gpio_request_one(BUZZER1, GPIOF_OUT_INIT_LOW, "SPEAKER");

   	/* cdev init */
	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &led_fops);
	cdev_add(cd_cdev, dev_num, 1);

	return 0;
}

static void __exit buzzer_exit(void){

	/* cdev free */
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);

	/* gpio free */
	gpio_set_value(BUZZER1, 0);
	gpio_free(BUZZER1);
}

module_init(buzzer_init);
module_exit(buzzer_exit);
