#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/cdev.h>

#define DEV_BUZZER "buzzer"

#define BUZZER_NUM 0x30
#define BUZZER_IOCTL_NUM1 BUZZER_NUM+1
#define BUZZER_IOCTL_NUM2 BUZZER_NUM+2
#define BUZZER_IOCTL_NUM3 BUZZER_NUM+3

#define BUZZER_IOCTL_NUM 'c'
#define BUZZER_ON _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM1, unsigned long *)
#define BUZZER_OFF _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM2, unsigned long *)
#define BUZZER_TIME _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM3, unsigned long *)

/* 나중에 이름을 pir_buzzer등으로 수정?? */
#define BUZZER 12

/* function : buzzer 
 * parameter : N/A
 * return : 0(success), -1(fail) */
static long buzzer(struct file *file, unsigned int cmd, unsigned long arg);

static void buzzer_do(unsigned long data);
static void buzzer_me(unsigned long data);
static void timer_buzzer(unsigned long data);
