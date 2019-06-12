#include <unistd.h>		
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
/* LED */
#define LED_IOCTL 0x10
#define LED_IOCTL_NUM1 LED_IOCTL+1
#define LED_IOCTL_NUM2 LED_IOCTL+2
#define LED_IOCTL_NUM3 LED_IOCTL+3
#define LED_IOCTL_NUM 'z'
#define TURN_ON_LED _IOWR(LED_IOCTL_NUM, LED_IOCTL_NUM1, unsigned long *)
#define TURN_OFF_LED _IOWR(LED_IOCTL_NUM, LED_IOCTL_NUM2, unsigned long *)
#define TIME_LED _IOWR(LED_IOCTL_NUM, LED_IOCTL_NUM3, unsigned long *)
/* LED Alert */
#define LED_ALERT_IOCTL 0x20
#define LED_ALERT_IOCTL_NUM1 LED_ALERT_IOCTL+1
#define LED_ALERT_IOCTL_NUM2 LED_ALERT_IOCTL+2
#define LED_ALERT_IOCTL_NUM3 LED_ALERT_IOCTL+3
#define LED_ALERT_IOCTL_NUM 'b'
#define TURN_ON_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM1, unsigned long *)
#define TURN_OFF_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM2, unsigned long *)
#define TIME_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM3, unsigned long *)
/* Buzzer */
#define IOCTL_START_NUM 0x80
#define IOCTL_NUM1 IOCTL_START_NUM+1
#define IOCTL_NUM2 IOCTL_START_NUM+2
#define IOCTL_NUM 'z'
#define BUZZER_DO(IOCTL_NUM, IOCTL_NUM1, unsigned long *)
#define BUZZER_ME(IOCTL_NUM, IOCTL_NUM2, unsigned long *)

int turn_on_led();
int turn_on_led_timer(unsigned long sec);
int turn_off_led();
int turn_on_led_alert();
int turn_on_led_alert_timer(unsigned long sec);
int turn_off_led_alert();

int turn_on_buzzer_me();
int turn_on_buzzer_do();

int turn_off_buzzer(int fd);

int read_light_sensor();

int turn_on_motor();
int turn_off_motor(int fd);
