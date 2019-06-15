#include "./sprinkler_lib.h"

/*스프링클러 작동여부 판단*/
int check_sprinkler(int data){
	int operation = false;
	/*습도 데이터가 일정 수준 이하이면 스프링클러를 작동신호를 출력*/
	if(data < 30){
		operation = true;
	}
	

	return operation;
}
