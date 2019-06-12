#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/fcntl.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

#define START_NUM 0x80
#define IOCTL_NUM1 START_NUM+1
#define IOCTL_NUM2 START_NUM+2
#define IOCTL_NUM3 START_NUM+3
#define IOCTL_NUM4 START_NUM+4
#define IOCTL_NUM5 START_NUM+5

#define KU_IOCTL_NUM 'z'
#define PIR_OPEN _IOWR(KU_IOCTL_NUM, IOCTL_NUM1, unsigned long *)
#define PIR_CLOSE _IOWR(KU_IOCTL_NUM, IOCTL_NUM2, unsigned long *)
#define PIR_READ _IOWR(KU_IOCTL_NUM, IOCTL_NUM3, unsigned long *)
#define PIR_FLUSH _IOWR(KU_IOCTL_NUM, IOCTL_NUM4, unsigned long *)
#define PIR_INSERT _IOWR(KU_IOCTL_NUM, IOCTL_NUM5, unsigned long *)
