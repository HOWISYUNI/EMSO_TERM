#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/cdev.h>

#define DEV_NAME "sprinkler"

#define MOTOR_A 6
#define MOTOR_B 13
#define MOTOR_C 19
#define MOTOR_D 26
#define WATERPUMP_A	12
#define WATERPUMP_B	13

#define STEPS 8

#define SPRINKLER_NUM 0x30
#define SPRINKLER_IOCTL_NUM1 SPRINKLER_NUM+1
#define SPRINKLER_IOCTL_NUM2 SPRINKLER_NUM+2
#define SPRINKLER_IOCTL_NUM3 SPRINKLER_NUM+3
#define SPRINKLER_IOCTL_NUM 'c'
#define SPRINKLER_ON _IOWR(SPRINKLER_IOCTL_NUM, SPRINKLER_IOCTL_NUM1, unsigned long *)
#define SPRINKLER_OFF _IOWR(SPRINKLER_IOCTL_NUM, SPRINKLER_IOCTL_NUM2, unsigned long *)
#define SPRINKLER_DELAY _IOWR(SPRINKLER_IOCTL_NUM, SPRINKLER_IOCTL_NUM3, unsigned long *)

#define MOTOR_SPEED 1000

/*delay 만큼 펌프 온*/
void pump_on(void);
/*펌프 오프. 아마 안쓰일거 같긴함.*/
void pump_off(void);
