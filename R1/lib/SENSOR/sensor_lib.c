#include "sensor_lib.h"
/* sensor library */

int turn_on_pir(){
	int ret;
	ret = open("/dev/pir", O_RDWR);
	
	return ret;	/* success : 0 */
}

int turn_off_pir(int fd){
	int ret;
	ret = close(fd);

	return ret;	/* success : 0 */
}

int turn_on_ultrasonic(){
	int ret;
	ret = open("/dev/ultrasonic", O_RDWR);

	return ret;	/* success : distance */
}

int turn_off_pir(int fd){
	int ret;
	ret = close(fd);

	return ret;	/* success : 0 */
}
