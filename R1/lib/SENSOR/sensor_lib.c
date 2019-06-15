/* sensor library */
#include "sensor_lib.h"

/*	read_light_senser()

Description : 빛 조도 값을 읽어오는 함수 (알아서 오픈하고 읽어서 닫고 읽은 값 리턴해줌)
Parameter : void
Return : int light_value

*/
int read_light_sensor()
{
	int dev;
	int ret;
	int light_value=0;

	dev = open("/dev/light_sensor_dev",O_RDWR);
	
	ret=read(dev,&light_value,sizeof(int));
	
	ret = close(dev);

	return light_value;
}


/*	read_soil_senser()			미구현!!

Description : 토양 온습도 값을 읽어오는 함수 (알아서 오픈하고 읽어서 닫고 읽은 값 리턴해줌)
Parameter : void
Return : int light_value

*/
int read_soil_sensor()
{
	int dev;
	int ret;
	int soil_value=0;

	dev = open("/dev/soil_sensor_dev",O_RDWR);
	
	ret=read(dev,&soil_value,sizeof(int));
	
	ret = close(dev);

	return soil_value;
}



/*	read_dht11_senser()

Description : 대기 중 온습도 값을 읽어오는 함수 (알아서 오픈하고 읽어서 닫고 읽은 값 리턴해줌)
Parameter : int dht11_data[4]   (습도 : dht11_data[0].dht11_data[1] / 온도 : dht11_data[2].dht11_data[3]도) 
Return : void

*/
int read_dht11_sensor()
{
	int dev;
	int ret;
	int dht11_data;

	dev = open("/dev/dht11_dev",O_RDWR);
	
	ret=read(dev,&dht11_data,sizeof(int));
	
	ret = close(dev);

	return dht11_data;

}


/*
	pir이나 ultrasonic 센서의 경우 시나리오상 한번씩 실행 되는 것이 아니라 계속 켜저서 값이 어느정도 이하 일 때, Interrupt가 	발생함.
*/

/* pir_wait()

Description : PIR Sensor에서 
Parameter : void
Return : 모션이 감지되었을 경우 0 return

*/
int pir_wait()
{
	int dev;
	int ret;

	dev = open("/dev/pir",O_RDWR);
	ret = ioctl(dev, DETECT_WAIT, NULL);    /* be wait in queue until detected */
	
	close(dev);

	return ret;
}

/*	open_ultrasonic_senser()

Description : 거리를 측정하는 센서를 켜는 함수
Parameter : void
Return : int dev (file description)

*/
int open_ultrasonic_sensor()
{
	int dev;
	int ulsn_value = 0;
	dev = open("/dev/ultrasonic_dev",O_RDWR);
	
	
	return dev;
}	
void close_ultrasonic_sensor(int dev)
{
	int ret;

	ret=close(dev);	
}
int read_ultrasonic_sensor(int dev)
{
	int ret;
	int ulsn_value = 0;

	ret = read(dev, &ulsn_value, sizeof(int));
	
	
	return ulsn_value;
}

/*	close_ultrasonic_senser()

Description : 거리를 측정하는 센서를 끄는 함수
Parameter : int dev  (file description)
Return : void

*/


