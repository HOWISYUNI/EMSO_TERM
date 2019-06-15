#include "./led_lib.h"

/*led 작동여부 판단*/
int check_led(int data){
	int operation = false;
	/*light sensor값이 일정 수준 이하이면 led를 작동하는 것으로 판단*/
	if(data < 500){
		operation = true;
	}

	return operation;
}
