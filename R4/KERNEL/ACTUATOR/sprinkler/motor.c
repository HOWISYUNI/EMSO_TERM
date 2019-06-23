#include "sprinkler.h"

MODULE_LICENSE("GPL");

static struct timer_list timer_m;
static dev_t dev_num;
static struct cdev *cd_cdev;
/* kthread task */
struct task_struct *cycling_motor;

static void timer_func(unsigned long data){
    /* Exception Handle */
    if(cycling_motor != NULL){
        kthread_stop(cycling_motor);
        printk("MOTOR_OFF_TIMER\n");
    }
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

void setStep(int pin1, int pin2, int pin3, int pin4){
	gpio_set_value(MOTOR_A, pin1);
	gpio_set_value(MOTOR_B, pin2);
	gpio_set_value(MOTOR_C, pin3);
	gpio_set_value(MOTOR_D, pin4);
}

void forward(int cycle, int delay){
	int i,j;
	
	for(i=0;i<cycle;i++){
		for(j=0;j<STEPS;j++){
			setStep(steps[j][0], steps[j][1], steps[j][2], steps[j][3]);
			udelay(delay);
		}
	}	
}

void backward(int cycle, int delay){
	int i,j;

	for(i=0;i<cycle;i++){
		for(j=STEPS-1;j>=0;j--){
			setStep(steps[j][0], steps[j][1], steps[j][2], steps[j][3]);
            udelay(delay);
		}
	}
}
/* direction
 * 0 : forward
 * 1 : backward */
void moveDegree(int degree, int delay, int direction){
        /* calculate degree
         * round one cycle is 0.703125
         */

        //float one_cycle_steps = 703125/1000000;
        long int cycle = (degree * 1000000 / 703125);

        if(direction == 0){
                forward(cycle, delay);
        }
        else{
                backward(cycle, delay);
        }
}
/* cycling */
int kthread_cycling(void *args){
    int i;
    set_current_state(TASK_INTERRUPTIBLE);
	
    /* cycling infinite */
    while(!kthread_should_stop()){
        for(i=0;i<24;i++){
            if(kthread_should_stop()){ 
                return 0;
            }
            moveDegree(15, MOTOR_SPEED, 0);
            msleep_interruptible(500);
        }
        for(i=0;i<24;i++){
            if(kthread_should_stop()){ 
                return 0;
            }
            moveDegree(15, MOTOR_SPEED, 1);
            msleep_interruptible(500);
        }
    }
    return 0;
}

static long motor(struct file *file, unsigned int cmd, unsigned long arg){

	switch(cmd){
		case MOTOR_ON:
		    /* kthread create & wake up */
		    /* Exception Handle */
		    if(cycling_motor == NULL){
    		    cycling_motor = kthread_run(kthread_cycling, NULL, "cycling");
    		    printk("MOTOR_ON\n");
		    }
		    break;
		case MOTOR_OFF:
		    /* kthread stop */
		    /* Exception Handle */
		    if(cycling_motor != NULL){
    		    kthread_stop(cycling_motor);
    		    printk("MOTOR_OFF\n");   
		    }
		    cycling_motor = NULL;
		    break;
		case MOTOR_TIMER:
    		del_timer(&timer_m); 
            timer_m.function = timer_func;
            timer_m.data = 1L;
            timer_m.expires = jiffies + (arg*HZ);
            if(cycling_motor != NULL){
                kthread_stop(cycling_motor);
    		    printk("MOTOR_OFF\n");
            }
		    cycling_motor = kthread_run(kthread_cycling, NULL, "cycling");
            add_timer(&timer_m);
            printk("MOTOR_ON_TIMER\n");
		    break;
		default:
			return -1;
	}

	return 0;
}

struct file_operations motor_fops = {
	.unlocked_ioctl = motor
};


static int __init motor_init(void){

    /* timer init */
    init_timer(&timer_m);
    cycling_motor = NULL;
    /* gpio init */
	gpio_request_one(MOTOR_A, GPIOF_OUT_INIT_LOW, "MOTOR_A");
	gpio_request_one(MOTOR_B, GPIOF_OUT_INIT_LOW, "MOTOR_B");
	gpio_request_one(MOTOR_C, GPIOF_OUT_INIT_LOW, "MOTOR_C");
	gpio_request_one(MOTOR_D, GPIOF_OUT_INIT_LOW, "MOTOR_D");
    /* cdev init */
	alloc_chrdev_region(&dev_num, 0, 1, DEV_MOTOR);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &motor_fops);
	cdev_add(cd_cdev, dev_num, 1);
	
	return 0;
}

static void __exit motor_exit(void){
    /* timer bye */
   	del_timer(&timer_m);
    /* kthread stop */
    if(cycling_motor != NULL){
        kthread_stop(cycling_motor);
        printk("MOTOR_OFF_EXIT\n");
    }
    
    /* gpio free */
	gpio_free(MOTOR_A);
	gpio_free(MOTOR_B);
	gpio_free(MOTOR_C);
	gpio_free(MOTOR_D);

    /* cdev free */
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
}

module_init(motor_init);
module_exit(motor_exit);
