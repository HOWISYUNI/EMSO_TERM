#include "save_data.h"

#define DEV_NAME "r3_ctl"

static long saveData_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
	int fd;
	loff_t pos = 0;
	struct file *file;
	mm_segment_t old_fs = get_fs();

	set_fs(KERNEL_DS);

	switch(cmd){
		case SOIL_SAVE:
			fd = sys_open("/home/pi/soil", ORWONLY | O_CREAT, 0644);
			if(fd >= 0){
				file = fget(fd);
				if(file){
					vfs_write(file, arg, strlen(arg), &pos);
					fput(file);
				}	
			}
			set_fs(old_fs);

			return 0;

		case DHT_SAVE:
			
			return 0;

		case LIGHT_SAVE:
			
			return 0;

		case ULSN_SAVE:

			return 0;

		case TEMP_SAVE:

			return 0;

		default:
			return -1;
	}
	return -1;
}

struct file_operations fops =
{
	.unlocked_ioctl = saveData_ioctl,	
};

static dev_t dev_num;
static struct cdev *cd_cdev;

static int __init ioctl_init(void){
	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &simple_char_fops);
	cdev_add(cd_cdev, dev_num, 1);

	return 0;
}

static void __exit ioctl_exit(void){
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);
}

module_init(ioctl_init);
module_exit(ioctl_exit);
