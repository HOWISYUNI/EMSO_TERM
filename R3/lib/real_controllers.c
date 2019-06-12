#include "controllers.h"

int dev, ret;

int save_data(int type, int data){
	switch(type){
		case SOIL:
			dev = open("/dev/r3_ctl", O_RDWR);
			ret = ioctl(dev, SOIL_SAVE, data);

			return 0;
			
		case DHT:
			dev = open("/dev/r3_ctl", O_RDWR);
			ret = ioctl(dev, DHT_SAVE, data);
		
			return 0;

		case LIGHT:
			dev = open("/dev/r3_ctl", O_RDWR);
            ret = ioctl(dev, LIGHT_SAVE, data);

			return 0;

		case DIST:
			dev = open("/dev/r3_ctl", O_RDWR);
            ret = ioctl(dev, ULSN_SAVE, data);

			return 0;

		default:
			return -1;
	}
}

int refine_data(int type, int data){
		
}
