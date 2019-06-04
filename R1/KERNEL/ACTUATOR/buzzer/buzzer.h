#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/cdev.h>

#define DEV_NAME "buzzer"

#define IOCTL_START_NUM 0x80
#define IOCTL_NUM1 IOCTL_START_NUM+1
#define IOCTL_NUM2 IOCTL_START_NUM+2

#define IOCTL_NUM 'z'
#define BUZZER_DO _IOWR(IOCTL_NUM, IOCTL_NUM1, unsigned long *)
#define BUZZER_ME _IOWR(IOCTL_NUM, IOCTL_NUM2, unsigned long *)

/* 나중에 이름을 pir_buzzer등으로 수정?? */
#define BUZZER1 12	
//#define BUZZER2 ??
//#define BUZZER3 ??

/* function : buzzer on
 * parameter : N/A
 * return : 0(success), -1(fail) */
static long buzzer_on(struct file *file, unsigned int cmd, unsigned long arg);

/* function : buzzer off
 * parameter : N/A
 * return : 0(success) */
static int buzzer_release(struct inode *inode, struct file *file);



