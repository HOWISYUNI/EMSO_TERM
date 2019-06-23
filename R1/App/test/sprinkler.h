#include <unistd.h>		
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

#define SPRNKLER 0x40
#define SPRNKLER_NUM1 SPRNKLER+1
#define SPRNKLER_NUM2 SPRNKLER+2
#define SPRNKLER_NUM3 SPRNKLER+3
#define SPRNKLER_NUM4 SPRNKLER+4
#define SPRNKLER_NUM5 SPRNKLER+5
#define SPRNKLER_NUM6 SPRNKLER+6

#define SPRNKLER_NUM 'd'
#define MOTOR_ON _IOWR(SPRNKLER_NUM, SPRNKLER_NUM1, unsigned long *)
#define MOTOR_OFF _IOWR(SPRNKLER_NUM, SPRNKLER_NUM2, unsigned long *)
#define MOTOR_TIMER _IOWR(SPRNKLER_NUM, SPRNKLER_NUM3, unsigned long *)
#define PUMP_ON _IOWR(SPRNKLER_NUM, SPRNKLER_NUM4, unsigned long *)
#define PUMP_OFF _IOWR(SPRNKLER_NUM, SPRNKLER_NUM5, unsigned long *)
#define PUMP_TIMER _IOWR(SPRNKLER_NUM, SPRNKLER_NUM6, unsigned long *)
