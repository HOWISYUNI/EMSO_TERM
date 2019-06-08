/* KU Smart Farm - Network - Data Communication - REST API
 * Msg    : @Request @Response
 * Method : @GET @POST @PUT
 * 
 */
#include "ksf_net.h"

static int ksf_net_open(struct inode *inode, struct file *file){
}

static int ksf_net_release(struct inode *inode, struct file *file){
}

static long ksf_net_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
}

static int ksf_net_read(struct file *file, char *buf, size_t len, loff_t *loff){
}

static int ksf_net_write(struct file *file, const char *buf, size_t len, loff_t *loff){
}

struct file_operations ksf_net_fops =
{
	.read = ksf_net_read,
	.write = ksf_net_write,
	.unlocked_ioctl = ksf_net_ioctl,
	.open = ksf_net_open,
	.release = ksf_net_release
};

static int __init ksf_net_init(void){

    /* Character Device init */
	alloc_chrdev_region(&dev_num, 0, 1, KSF_NET);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &ksf_net_fops);
	cdev_add(cd_cdev, dev_num, 1);
	
    return 0;
}

static void __exit ksf_net_exit(void){

    /* Character Device free */
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);
	
}


module_init(ksf_net_init);
module_exit(ksf_net_exit);
