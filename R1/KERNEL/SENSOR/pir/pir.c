#include "pir.h"

MODULE_LICENSE("GPL");

static int detect = FALSE;
static int irq_num;
wait_queue_head_t wq;

static long pir_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
    switch(cmd){
        case DETECT_WAIT:
            enable_irq(irq_num);
            detect = FALSE;
            printk("wait!\n");
            wait_event(wq, detect == TRUE); /* wake up when detected from isr */
            disable_irq(irq_num);
	    	
			printk("return!\n");
            return 0;
	            
        default :
            return -1;
    }
}

struct file_operations pir_fops =
{
	.unlocked_ioctl = pir_ioctl,
};

static irqreturn_t pir_isr(int irq, void* dev_id){
	detect = TRUE;
	printk("wake up!\n");
	wake_up(&wq);

	return IRQ_HANDLED;
}

static dev_t dev_num;
static struct cdev *cd_cdev;

static int __init pir_init(void){
	int ret;

    /* wait queue init */
    init_waitqueue_head(&wq);

    /* cdev init */
	alloc_chrdev_region(&dev_num, 0, 1, DEV_PIR);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &pir_fops);
	cdev_add(cd_cdev, dev_num, 1);

    /* gpio & interrupt init */
	gpio_request_one(SENSOR, GPIOF_IN, "pir");
	irq_num = gpio_to_irq(SENSOR);
	ret = request_irq(irq_num, pir_isr, IRQF_TRIGGER_RISING, "pir", NULL);
	
	/* irq fail */
	if(ret){
		printk(KERN_ERR "Unable to request IRQ: %d\n", ret);
		free_irq(irq_num, NULL);
	}
	/* success */
	else{
	   	disable_irq(irq_num);
	}
	
	printk("PIR Init\n");

	return 0;
}

static void __exit pir_exit(void){
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);

    disable_irq(irq_num);

	free_irq(irq_num, NULL);
	gpio_free(SENSOR);
}

module_init(pir_init);
module_exit(pir_exit);
