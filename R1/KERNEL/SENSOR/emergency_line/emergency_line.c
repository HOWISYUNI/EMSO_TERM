/*
 * 20190624 aeomhs
 * emergency_line.c
 * */
#include "emergency_line.h"

MODULE_LICENSE("GPL");

static dev_t dev_num;
static struct cdev *cd_cdev;

static long emg_line_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
        switch( cmd ){
        case EMG_ON:
                printk("emergency line up\n");
                gpio_set_value(EMG_PIN, 1);
                gpio_set_value(EMG_PIN, 0);
                break;
        case EMG_OFF:
                printk("emergency line down\n");
                gpio_set_value(EMG_PIN, 0);
                break;
        default:
                return -1;
        }

        return 0;
}

struct file_operations emg_line_fops = {
	.unlocked_ioctl = emg_line_ioctl,
};

static int __init emg_line_init(void){
    /* gpio init */
    gpio_request_one(EMG_PIN, GPIOF_OUT_INIT_LOW, "emergency");

    /* cdev init */
    alloc_chrdev_region(&dev_num, 0, 1, DEV_EMG);
    cd_cdev = cdev_alloc();
    cdev_init(cd_cdev, &emg_line_fops);
    cdev_add(cd_cdev, dev_num, 1);
	
    return 0;
}

static void __exit emg_line_exit(void){

    /* cdev free */
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
    /* gpio free */
    gpio_free(EMG_PIN);
    
}

module_init(emg_line_init);
module_exit(emg_line_exit);
