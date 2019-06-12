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
void read_dht11_sensor(int dht11_data[])
{
	int dev;
	int ret;

	dev = open("/dev/dht11_dev",O_RDWR);
	
	ret=read(dev,dht11_data,4*sizeof(int));
	
	ret = close(dev);

}


/*
	pir이나 ultrasonic 센서의 경우 시나리오상 한번씩 실행 되는 것이 아니라 계속 켜저서 값이 어느정도 이하 일 때, Interrupt가 	발생함.
*/

/*	open_pir_senser()

Description : 모션을 감지하는 센서를 켜는 함수
Parameter : void
Return : int dev (file description)

*/
int open_pir_sensor()
{
	int dev;
	int ret;

	dev = open("/dev/pir_sensor_dev",O_RDWR);
	
	return dev

}

/*	close_pir_senser()

Description : 모션을 감지하는 센서를 끄는 함
Parameter : int dev  (file description)
Return : void

*/

void close_pir_sensor(int dev)
{
	int ret;

	ret = close(dev);

}


/*	open_ultrasonic_senser()

Description : 거리를 측정하는 센서를 켜는 함수
Parameter : void
Return : int dev (file description)

*/
int open_ultrasonic_sensor()
{
	int dev;
	int ret;

	dev = open("/dev/ultrasonic_sensor_dev",O_RDWR);
	
	return dev

}

/*	close_ultrasonic_senser()

Description : 거리를 측정하는 센서를 끄는 함수
Parameter : int dev  (file description)
Return : void

*/

void close_ultrasonic_sensor(int dev)
{
	int ret;

	ret = close(dev);
}
