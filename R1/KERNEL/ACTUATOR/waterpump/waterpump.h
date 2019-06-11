#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/cdev.h>

#define DEV_NAME "waterpump"

#define WATERPUMP_A	12
#define WATERPUMP_B	13

/*delay 만큼 펌프 온*/
void pump_on(int delay);
/*펌프 오프. 아마 안쓰일거 같긴함.*/
void pump_off(void);

static int waterpump_open(struct inode *inode, struct file *file);

static int waterpump_release(struct inode *inode, struct file *file);


