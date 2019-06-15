#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEV_NAME "dht11_dev"

#define MAX_TIMING 85
#define DHT 21

/*
	function : dht11 on
*/
static void dht_read(void);
/*
	function : dht11 repeat 
*/
static int dht11_open(struct inode *inode, struct file *file);

static int dht11_read(struct file *file, char *buf, size_t len, loff_t *lof);
