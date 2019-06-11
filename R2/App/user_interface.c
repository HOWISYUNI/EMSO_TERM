#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int input;

	struct request rcv;

	int socket_r1 = client_open(dest_ip, port);
	int socket_r3 = client_open(dest_ip, port);

	while(1){
		system("clear");
		printf("-----------------------------------------\n");
		printf("* 1. 스프링클러 켜기                    *\n");
		printf("* 2. led 켜기                            \n");
		printf("-----------------------------------------\n");
		scanf("%d", &input);

		if(input == 1){
			
		}else if(input == 2){
			
		}else if(){

		}

	}


	return 0;
}
