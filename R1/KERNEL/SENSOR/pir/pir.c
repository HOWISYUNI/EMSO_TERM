#include "pir.h"

MODULE_LICENSE("GPL");

static int a = 0;
static int irq_num;
wait_queue_head_t wq;

static long pir_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
	enable_irq(irq_num);

	if(cmd == (0x80+1)){
		wait_event(wq, a != 0);

		a = 0;
		disable_irq(irq_num);

		return 0;
	}

	return -1;
}

struct file_operations pir_fops =
{
	.open = pir_open,
	.release = pir_release,
	.unlocked_ioctl = pir_ioctl,
};

static irqreturn_t pir_isr(int irq, void* dev_id){
	a = 1;
	wake_up(&wq);

	return IRQ_HANDLED;
}

static dev_t dev_num;
static struct cdev *cd_cdev;

static int __init pir_init(void){
	int ret;

	printk("Init PIR Module!!\n");

	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &pir_fops);
	cdev_add(cd_cdev, dev_num, 1);

	gpio_request_one(SENSOR, GPIOF_IN, "pir");
	irq_num = gpio_to_irq(SENSOR);
	ret = request_irq(irq_num, pir_isr, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "pir_irq", NULL);
	
	/* fail */
	if(ret){
		printk(KERN_ERR "Unable to request IRQ: %d\n", ret);
		free_irq(irq_num, NULL);
	}
	/* success */
	else
	   	disable_irq(irq_num);

	init_waitqueue_head(&wq);

	return 0;
}

static void __exit pir_exit(void){
	printk("Exit PIR Module!!\n");
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);

	free_irq(irq_num, NULL);
	gpio_free(SENSOR);
}

module_init(pir_init);
module_exit(pir_exit);
