#include "./sprinkler_lib.h"

/*스프링클러 작동여부 판단*/
int check_sprinkler(int data){
	int operation = false;
	/*습도 데이터가 클수록 건조한거. 습도데이터가 일정 값보다 크면 스프링클러를 작동*/
	if(data > 700){
		operation = true;
	}
	

	return operation;
}
