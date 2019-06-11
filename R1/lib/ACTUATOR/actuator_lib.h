#include <sys/fcntl.h>		
#include <unistd.h>		
#include <sys/fcntl.h>
#include <sys/ioctl.h>

/* close */

#define IOCTL_START_NUM 0x80
#define IOCTL_NUM1 IOCTL_START_NUM+1
#define IOCTL_NUM2 IOCTL_START_NUM+2

#define IOCTL_NUM 'z'
#define BUZZER_DO(IOCTL_NUM, IOCTL_NUM1, unsigned long *)
#define BUZZER_ME(IOCTL_NUM, IOCTL_NUM2, unsigned long *)

int turn_on_led();
int turn_off_led(int fd);
int turn_on_led_alert();
int turn_off_led_alert(int fd);

int turn_on_buzzer_me();
int turn_on_buzzer_do();

int turn_off_buzzer(int fd);

int read_light_sensor();

int turn_on_motor();
int turn_off_motor(int fd);
