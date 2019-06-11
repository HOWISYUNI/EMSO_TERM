/* 20190602 hanyh buzzer함수 구현 */
#include "buzzer.h"

MODULE_LICENSE("GPL");

int notes[] = {1911, 1516};	//도, 미
int i;

/* 부저가 여러 개가 되면 ioctl로 분리하자! */
static long buzzer_on(struct file *file, unsigned int cmd, unsigned long arg){
	int j = 0;
	gpio_set_value(BUZZER1, 1);
	switch(cmd){
		case BUZZER_DO:
			/* 도 */
			for(j = 0; j< 100; j++){
				gpio_set_value(BUZZER1, 1);
				udelay(notes[0]);
				gpio_set_value(BUZZER1, 0);
				udelay(notes[0]);
			}
			break;

		case BUZZER_ME:
			/* 미 */
			for(j = 0; j < 100; j++){
				gpio_set_value(BUZZER1, 1);
				udelay(notes[1]);
				gpio_set_value(BUZZER1, 0);
				udelay(notes[1]);
			}
			break;
		
		default:
			return -1;
	}

	return 0;
}

static int buzzer_release(struct inode *inode, struct file *file){
	gpio_set_value(BUZZER1, 0);
	
	return 0;
}

struct file_operations buzzer_fops = {
	.unlocked_ioctl = buzzer_on,
	.release = buzzer_release,
};

static dev_t dev_num;
static struct cdev *cd_cdev;

static int __init buzzer_on_init(void){
	gpio_request_one(BUZZER1, GPIOF_OUT_INIT_LOW, "BUZZER");

   	/* cdev init */
	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &buzzer_fops);
	cdev_add(cd_cdev, dev_num, 1);

	return 0;
}

static void __exit buzzer_on_exit(void){
	/* cdev free */
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);

	/* gpio free */
	gpio_set_value(BUZZER1, 0);
	gpio_free(BUZZER1);
}

module_init(buzzer_on_init);
module_exit(buzzer_on_exit);
