/* LED */
#ifndef LED_DEF
#define LED_DEF

#define LED 4
#define DEV_LED "led"

#define LED_IOCTL 0x10
#define LED_IOCTL_NUM1 LED_IOCTL+1
#define LED_IOCTL_NUM2 LED_IOCTL+2
#define LED_IOCTL_NUM3 LED_IOCTL+3
#define LED_IOCTL_NUM 'a'
#define TURN_ON_LED _IOWR(LED_IOCTL_NUM, LED_IOCTL_NUM1, unsigned long *)
#define TURN_OFF_LED _IOWR(LED_IOCTL_NUM, LED_IOCTL_NUM2, unsigned long *)
#define TIME_LED _IOWR(LED_IOCTL_NUM, LED_IOCTL_NUM3, unsigned long *)
#endif

/* LED Alert */
#ifndef LED_ALERT_DEF
#define LED_ALERT_DEF


#define LED_ALERT 5
#define DEV_LED_ALERT "led_alert"

#define LED_ALERT_IOCTL 0x20
#define LED_ALERT_IOCTL_NUM1 LED_ALERT_IOCTL+1
#define LED_ALERT_IOCTL_NUM2 LED_ALERT_IOCTL+2
#define LED_ALERT_IOCTL_NUM3 LED_ALERT_IOCTL+3
#define LED_ALERT_IOCTL_NUM 'b'
#define TURN_ON_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM1, unsigned long *)
#define TURN_OFF_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM2, unsigned long *)
#define TIME_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM3, unsigned long *)

#endif

/* Buzzer */
#ifndef BUZZER_DEF
#define BUZZER_DEF

#define BUZZER 25
#define DEV_BUZZER "buzzer"
#define BUZZER_NUM 0x30
#define BUZZER_IOCTL_NUM1 BUZZER_NUM+1
#define BUZZER_IOCTL_NUM2 BUZZER_NUM+2
#define BUZZER_IOCTL_NUM3 BUZZER_NUM+3
#define BUZZER_IOCTL_NUM 'c'
#define BUZZER_ON _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM1, unsigned long *)
#define BUZZER_OFF _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM2, unsigned long *)
#define BUZZER_TIME _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM3, unsigned long *)
#endif

/* Sprinkler */
#ifndef SPRINKLER_DEF
#define SPRINKLER_DEF

#define MOTOR_A 6
#define MOTOR_B 13
#define MOTOR_C 19
#define MOTOR_D 26
#define WATERPUMP_A	12
#define WATERPUMP_B	24

#define DEV_MOTOR "motor"
#define DEV_WTPMP "water_pump"

#define SPRNKLER 0x10
#define SPRNKLER_NUM1 SPRNKLER+1
#define SPRNKLER_NUM2 SPRNKLER+2
#define SPRNKLER_NUM3 SPRNKLER+3
#define SPRNKLER_NUM4 SPRNKLER+4
#define SPRNKLER_NUM5 SPRNKLER+5
#define SPRNKLER_NUM6 SPRNKLER+6
#define SPRNKLER_NUM 'k'
#define MOTOR_ON _IOWR(SPRNKLER_NUM, SPRNKLER_NUM1, unsigned long *)
#define MOTOR_OFF _IOWR(SPRNKLER_NUM, SPRNKLER_NUM2, unsigned long *)
#define MOTOR_TIMER _IOWR(SPRNKLER_NUM, SPRNKLER_NUM3, unsigned long *)
#define PUMP_ON _IOWR(SPRNKLER_NUM, SPRNKLER_NUM4, unsigned long *)
#define PUMP_OFF _IOWR(SPRNKLER_NUM, SPRNKLER_NUM5, unsigned long *)
#define PUMP_TIMER _IOWR(SPRNKLER_NUM, SPRNKLER_NUM6, unsigned long *)
#endif

/* dht */
#ifndef DHT_DEF
#define DHT_DEF

#define DHT 21
#define DEV_DHT "dht11_dev"
#endif

/* light sensor */
#ifndef LIGHT_DEF
#define LIGHT_DEF

#define MOSI 10
#define MISO 9
#define SCLK 11
#define CE0 8
#define DEV_LIGHT "light_sensor_dev"
#endif

/* PIR */
#ifndef PIR_DEF
#define PIR_DEF

#define SENSOR 17
#define DEV_PIR "pir"

#define PIR_IOCTL 0x60
#define PIR_IOCTL_NUM1 PIR_IOCTL+1
#define PIR_IOCTL_NUM 'p'
#define DETECT_WAIT _IOWR(PIR_IOCTL_NUM, PIR_IOCTL_NUM1, unsigned long *)
#endif

/* Soil */
#ifndef SOIL_DEF
#define SOIL_DEF

#define MOSI 10
#define MISO 9
#define SCLK 11
#define CE1 7

#define DEV_SOIL "soil_sensor_dev"
#endif

#ifndef ULTRA_DEF
#define ULTRA_DEF

#define TRIG 23
#define ECHO 27

#define DEV_ULTRA "ultrasonic_dev"
#endif
