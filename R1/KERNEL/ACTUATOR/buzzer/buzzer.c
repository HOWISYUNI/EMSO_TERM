/* 20190602 hanyh buzzer함수 구현 */
/* 20190613 aeomhs add timer */
#include "buzzer.h"
#define DO 0
#define ME 1

MODULE_LICENSE("GPL");

static struct timer_list timer;
static struct timer_list end_timer;
static dev_t dev_num;
static struct cdev *cd_cdev;

static int notes[] = {1911, 1516};	//도, 미

static void buzzer_do(unsigned long data){
    int i;
	timer.function = buzzer_me;
	timer.expires = jiffies + (HZ);
    /* 도 */
	for(i = 0; i< 100; i++){
		gpio_set_value(BUZZER, 1);
		udelay(notes[DO]);
		gpio_set_value(BUZZER, 0);
		udelay(notes[DO]);
	}
	add_timer(&timer);
}

static void buzzer_me(unsigned long data){
    int j;
	timer.function = buzzer_do;
	timer.expires = jiffies + (HZ);
    /* 미 */
	for(j = 0; j < 100; j++){
		gpio_set_value(BUZZER, 1);
		udelay(notes[ME]);
		gpio_set_value(BUZZER, 0);
		udelay(notes[ME]);
	}
	add_timer(&timer);
}

static void timer_buzzer(unsigned long data){
    del_timer(&timer);
    gpio_set_value(BUZZER, 0);
}

/* 부저가 여러 개가 되면 ioctl로 분리하자! */
static long buzzer(struct file *file, unsigned int cmd, unsigned long arg){
		
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

struct file_operations buzzer_fops = {
	.unlocked_ioctl = buzzer
};


static int __init buzzer_on_init(void){
    /* timer init */
    init_timer(&timer);
    init_timer(&end_timer);
    
    /* gpio init */
	gpio_request_one(BUZZER, GPIOF_OUT_INIT_LOW, "BUZZER");

   	/* cdev init */
	alloc_chrdev_region(&dev_num, 0, 1, DEV_BUZZER);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &buzzer_fops);
	cdev_add(cd_cdev, dev_num, 1);

	return 0;
}

static void __exit buzzer_on_exit(void){
    /* timer bye */
   	del_timer(&timer);
   	del_timer(&end_timer);
   	
	/* cdev free */
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);

	/* gpio free */
	gpio_set_value(BUZZER, 0);
	gpio_free(BUZZER);
}

module_init(buzzer_on_init);
module_exit(buzzer_on_exit);
