#include "actuator_lib.h"
/* LED device path : /dev/LED
   BUZZER device path : /dev/buzzer */

/* turn on led */
int turn_on_led(){
    int ret;
    ret = open("/dev/led", O_RDWR);
    return ret;
}

/* turn off led */
int turn_off_led(int fd){
    int ret;
    ret = close(fd);
    return ret;
}

/* buzzer on '미' */
int turn_on_buzzer_me(){
	int ret;
	dev = open("/dev/buzzer", O_RDWR);
	ret = ioctl(dev, BUZZER_ME, NULL);

	return ret;	/* success = 0 */
}
/* buzzer on '도' */
int turn_on_buzzer_do(){
	int ret;
	dev = open("/dev/buzzer", O_RDWR);
	ret = ioctl(dev, BUZZER_DO, NULL);

	return ret;	/* success = 0 */
}

/* buzzer off */
int turn_off_buzzer(int fd){
	int ret;
	ret = close(fd);
	return ret;
}

/* read value from light sensor*/
int read_light_sensor(){
	int dev;
	int ret;
	int light_value=0;

	dev = open("/dev/light_sensor_dev",O_RDWR);
	
	ret=read(dev,&light_value,sizeof(int));
	
	ret = close(dev);

	return light_value;
}
