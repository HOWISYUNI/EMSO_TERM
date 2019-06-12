#include "app.h"

/* led device file descriptor */
static int led = 0;
static int buzzer = 0;
static int sonic = 0;
static int pir = 0;

/* @flag:0 -> turn led off 
 * @flag:1 -> turn led on  */
int led_controller(int flag){
    int ret;

    if(flag == 0){
        /* led off */
        ret = turn_off_led(led);
	return ret;
    }
    else{
        /* led on */
	led = turn_on_led();
	return led;
    }
}

/* emergency buzzer controller */
int buzzer_controller(int count, int flag){
	int ret;

	if(flag == 0){
		while(count != 0){
			/* 미 */
			ret = turn_on_buzzer_me();

			sleep(1);
			/* 도 */
			ret = turn_on_buzzer_do();

			count--;
		}
		return ret;
	}
	else{
		ret = turn_off_buzzer(buzzer);

		return ret;
	}
}

int ultrasonic_controller(int flag){
	int ret;

	if(flag == 0){
		ret = turn_off_ultrasonic(sonic);

		return ret;
	}
	else{
		sonic = turn_on_ultrasonic();

		return sonic;
	}	
}

int pir_controller(int flag){
	int ret;

	if(flag == 0){
		ret = turn_off_pir(pir);

		return ret;
	}
	else{
		pir = turn_on_pir();
	
		return pir;
	}
}
