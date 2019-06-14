#include "sprinkler.h"

MODULE_LICENSE("GPL");

static dev_t dev_num;
static struct cdev *cd_cdev;

/*delay 시간만큼 워터펌프 온*/
void pump_on(){
	printk("pump on");
	/*이게 지금 작동은하는데 물이 어떻게 들어가는지는 잘 모르겠음*/
	gpio_set_value(WATERPUMP_A, 1);
	gpio_set_value(WATERPUMP_B, 0);
	

}

/*펌프 오프 근데 아마 안쓰일거 같음*/
void pump_off(){
	printk("pump off");

	gpio_set_value(WATERPUMP_A, 0);
	gpio_set_value(WATERPUMP_B, 0);

}


int steps[STEPS][4] = {
	{1,0,0,0},
	{1,1,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,0,1,0},
	{0,0,1,1},
	{0,0,0,1},
	{1,0,0,1}
};

void setStep(int step){
	gpio_set_value(MOTOR_A, steps[step][0]);
    gpio_set_value(MOTOR_B, steps[step][1]);
    gpio_set_value(MOTOR_C, steps[step][2]);
    gpio_set_value(MOTOR_D, steps[step][3]);
}

void forward(int round, int delay){
	int i=0;
	int j=0;
	for(i=1;i<=64*round;i++){
		for(j=1;j<=64;j++){//5.625도
			setStep(j%8);
			udelay(delay);
		}
	}

}

void move_degree(int degree, int delay, int direction){
	int i=0;
	if(direction == 0){
		for(i=1;i<=(64*64*degree)/360;i++){//360도
			setStep(i%8);
			udelay(delay);
		}

	}else{
		for(i=1;i<=(64*64*degree)/360;i++){
			setStep(STEPS-i%8);
			udelay(delay);
		}	
	}

}

static int sprinkler_open(struct inode *inode, struct file *file){
	return 0;
}

static int sprinkler_release(struct inode *inode, struct file *file){
	return 0;
}



static long sprinkler_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
	int i = 0;		
	int d = (int)arg;
	switch(cmd){
		/*case SPRINKLER_ON:
		    del_timer(&timer);
	    	timer.function = buzzer_me;
        	timer.expires = jiffies + (HZ);
        	add_timer(&timer);
			gpio_set_value(BUZZER, 1);
			break;

		case sprinkler_OFF:
		    del_timer(&timer);
			gpio_set_value(BUZZER, 0);
			break;
			
		case sprinkler_TIME:
		    del_timer(&timer);
		    timer.function = buzzer_me;
        	timer.expires = jiffies + (HZ);
        	add_timer(&timer);
			gpio_set_value(BUZZER, 1);
			
		    del_timer(&end_timer);
			end_timer.function = timer_buzzer;
			end_timer.expires = jiffies + (arg*HZ);
		    add_timer(&end_timer);
		    break;*/

		//jinhoski가 구현한부분
		case SPRINKLER_ON:
			gpio_set_value(WATERPUMP_A, 1);
			gpio_set_value(WATERPUMP_B, 0);
			while(1){
				move_degree(360, MOTOR_SPEED, 1);
				move_degree(360, MOTOR_SPEED, 0);
			}
		case SPRINKLER_OFF:
		   	gpio_set_value(WATERPUMP_A, 0);
			gpio_set_value(WATERPUMP_B, 0);
			
		case SPRINKLER_DELAY:
			gpio_set_value(WATERPUMP_A, 1);
            		gpio_set_value(WATERPUMP_B, 0);
			
			for(i=0;i<d;i++){
				move_degree(360, MOTOR_SPEED, 1);
				move_degree(360, MOTOR_SPEED, 0);
			}
			gpio_set_value(WATERPUMP_A, 0);
			gpio_set_value(WATERPUMP_B, 0);
		default:
			return -1;
	}

	return 0;
}

struct file_operations sprinkler_fops = {
	.open = sprinkler_open,
	.release = sprinkler_release,
	.unlocked_ioctl = sprinkler_ioctl,
};


static int __init sprinkler_init(void){
	gpio_request_one(MOTOR_A, GPIOF_OUT_INIT_LOW, "MOTOR_A");
	gpio_request_one(MOTOR_B, GPIOF_OUT_INIT_LOW, "MOTOR_B");
	gpio_request_one(MOTOR_C, GPIOF_OUT_INIT_LOW, "MOTOR_C");
	gpio_request_one(MOTOR_D, GPIOF_OUT_INIT_LOW, "MOTOR_D");
	gpio_request_one(WATERPUMP_A, GPIOF_OUT_INIT_LOW, "PUMP_A");
	gpio_request_one(WATERPUMP_B, GPIOF_OUT_INIT_LOW, "PUMP_B");



	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &sprinkler_fops);
	cdev_add(cd_cdev, dev_num, 1);
	
	return 0;
}

static void __exit sprinkler_exit(void){
	gpio_free(MOTOR_A);
	gpio_free(MOTOR_B);
	gpio_free(MOTOR_C);
	gpio_free(MOTOR_D);
	gpio_set_value(WATERPUMP_A, 0);
	gpio_set_value(WATERPUMP_B, 0);

	gpio_free(WATERPUMP_A);
	gpio_free(WATERPUMP_B);
}

module_init(sprinkler_init);
module_exit(sprinkler_exit);
