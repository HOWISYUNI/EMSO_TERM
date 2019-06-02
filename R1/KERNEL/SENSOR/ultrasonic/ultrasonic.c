#include "ultrasonic.h"

MODULE_LICENSE("GPL");

/*
static dev_t dev_num;
static struct cdev *cd_cdev;
*/
static int dist;
static int count = 0;
static int irq_num = -1;
static int echo_flag = 0;

//static ktime_t start;
//static ktime_t stop;

static int ultrasonic_read(void) {
	count = 0;
	gpio_set_value(TRIG, 1);
	udelay(10);
	gpio_set_value(TRIG, 0);
	echo_flag = 0;

	while(echo_flag == 0){
		count++;
		udelay(1);
	}
	
	dist = (34000 * count) / 2000000;

	return dist;
}

static irqreturn_t ultrasonic_isr(int irq, void* dev_id){
	//ktime_t time_value;

	if(echo_flag == 0){
		//time_value = ktime_get();
		if(gpio_get_value(ECHO) == 0){
		//	start = time_value;
		//}
		//else{
		//	stop = time_value;
			echo_flag = 1;
		}
	}
	return IRQ_HANDLED;
}

static int __init ultrasonic_init(void){
	int ret, sec, i;

	printk("Init ultrasonic Module!!\n");

	ret = gpio_request_one(TRIG, GPIOF_DIR_OUT, "TRIG");
	if(ret < 0){
		printk(KERN_ERR "Failed to request gpio for TRIG(%d)\n", ret);
		return -1;
	}

	ret = gpio_request_one(ECHO, GPIOF_DIR_IN, "ECHO");
	if(ret < 0){
		printk(KERN_ERR "Failed to request gpio for ECHO(%d)\n", ret);
		return -1;
	}

	ret = gpio_to_irq(ECHO);
	if(ret < 0){
		printk(KERN_ERR "Failed to set gpio IRQ(%d)\n", ret);
		return -1;
	}
	else{
		irq_num = ret;
	}

	ret = request_irq(irq_num, ultrasonic_isr, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "ultrasonic_irq", NULL);
	if(ret){
		printk(KERN_ERR "Failed to request IRQ(%d)\n", ret);
		return -1;	
	}

	for(i = 0; i < 10; i++){
		sec = ultrasonic_read();
		printk("sec : %dcm\n", sec);
		mdelay(4000);
	}

	return 0;
}

static void __exit ultrasonic_exit(void){
	printk("Exit ultra_sonic Module!!\n");

	if(irq_num != -1){
		free_irq(irq_num, NULL);
	}
	gpio_free(TRIG);
	gpio_free(ECHO);
}

module_init(ultrasonic_init);
module_exit(ultrasonic_exit);
