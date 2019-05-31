#include "device_lib.h"
/* LED device path : /dev/LED */

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

int turn_on_pir(){
	int ret;
	ret = open("/dev/pir", O_RDWR);
	
	return ret;	/* success : 0 */
}

int turn_off_led(int fd){
	int ret;
	ret = close(fd);

	return ret;	/* success : 0 */
}
