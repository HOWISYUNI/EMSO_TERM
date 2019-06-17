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

/* ULTRA */
#ifndef ULTRA_DEF
#define ULTRA_DEF

#define TRIG 23
#define ECHO 27

#define DEV_ULTRA "ultrasonic_dev"
#endif
