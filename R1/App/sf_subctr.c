#include "app.h"

/* led device file descriptor */
static int led = 0;

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
