#include <stdio.h>
#include <unistd.h>		
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <wait.h>
/* LED */
#define LED_IOCTL 0x10
#define LED_IOCTL_NUM1 LED_IOCTL+1
#define LED_IOCTL_NUM2 LED_IOCTL+2
#define LED_IOCTL_NUM3 LED_IOCTL+3
#define LED_IOCTL_NUM 'a'
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
#define BUZZER_NUM 0x30
#define BUZZER_IOCTL_NUM1 BUZZER_NUM+1
#define BUZZER_IOCTL_NUM2 BUZZER_NUM+2
#define BUZZER_IOCTL_NUM3 BUZZER_NUM+3
#define BUZZER_IOCTL_NUM 'c'
#define BUZZER_ON _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM1, unsigned long *)
#define BUZZER_OFF _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM2, unsigned long *)
#define BUZZER_TIME _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM3, unsigned long *)
/* Sprinkler */
#define SPRNKLER 0x40
#define SPRNKLER_NUM1 SPRNKLER+1
#define SPRNKLER_NUM2 SPRNKLER+2
#define SPRNKLER_NUM3 SPRNKLER+3
#define SPRNKLER_NUM4 SPRNKLER+4
#define SPRNKLER_NUM5 SPRNKLER+5
#define SPRNKLER_NUM6 SPRNKLER+6
#define SPRNKLER_NUM7 SPRNKLER+7
#define SPRNKLER_NUM8 SPRNKLER+8
#define SPRNKLER_NUM 'd'
#define MOTOR_ON _IOWR(SPRNKLER_NUM, SPRNKLER_NUM1, unsigned long *)
#define MOTOR_OFF _IOWR(SPRNKLER_NUM, SPRNKLER_NUM2, unsigned long *)
#define MOTOR_TIMER _IOWR(SPRNKLER_NUM, SPRNKLER_NUM3, unsigned long *)
#define PUMP_ON _IOWR(SPRNKLER_NUM, SPRNKLER_NUM4, unsigned long *)
#define PUMP_OFF _IOWR(SPRNKLER_NUM, SPRNKLER_NUM5, unsigned long *)
#define PUMP_TIMER _IOWR(SPRNKLER_NUM, SPRNKLER_NUM6, unsigned long *)
#define PIN_TEST_A _IOWR(SPRNKLER_NUM, SPRNKLER_NUM7, unsigned long *)
#define PIN_TEST_B _IOWR(SPRNKLER_NUM, SPRNKLER_NUM8, unsigned long *)
/* LED & LED for ALERT */
int turn_on_led(void);
int turn_on_led_timer(unsigned long sec);
int turn_off_led(void);
int turn_on_led_alert(void);
int turn_on_led_alert_timer(unsigned long sec);
int turn_off_led_alert(void);
/* Buzzer */
int turn_on_buzzer(void);
int turn_off_buzzer(void);
int turn_on_buzzer_timer(unsigned long sec);
/* Sprinkler */
int turn_on_sprinkler(void);
int turn_off_sprinkler(void);
int timer_sprinkler(unsigned long sec);
/* Camera */
int snapshot();
