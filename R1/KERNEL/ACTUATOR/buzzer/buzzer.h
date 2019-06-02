#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/cdev.h>

#define DEV_NAME "buzzer"

/* 나중에 이름을 pir_buzzer등으로 수정?? */
#define BUZZER1 12	
//#define BUZZER2 ??
//#define BUZZER3 ??

/* function : buzzer on
 * parameter : N/A
 * return : file desciptor */
int buzzer_open(struct inode *inode, struct file *file);

/* function : buzzer off
 * parameter : N/A
 * return : file descriptor */
int buzzer_release(struct inode *inode, struct file *file);




