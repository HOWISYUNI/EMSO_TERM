#include <stdio.h>
#include <unistd.h>

#include "app.h"

/*
> Usage  : R2.cmd_ctl.client->R1.act_ctl.server  
> method : 'U' (should be fixed)  
> type   : led_light('l'), led_alert('a'), buzzer('b')  
>           , camera('c'), motor('m'), water_pump('p'), sprinkler('s'),    
> cmd    : turn_on('1'), turn_off('0')  
> len    : data length  
> data   : timer(positive), infinit(zero), error(negative)
*/

int main(void){
	int socket_r2;
	int fd;
	struct request rcv;

   	socket_r2 = server_open(R2_DATA_PORT);

	/*요청 대기*/
	while(1){
		rcv = wait_request(socket_r1);

		if(rcv.type == "l"){	/*온습도 데이터*/
			
		}else if(rcv.type == "a"){	/*조도 데이터*/
			
		}else if(rcv.type == "b"){	/*비정상 상황 신호*/
			
		}else if(rcv.type == "c"){	/*미확인 물체 신호*/
			
		}else if(rcv.type == "s"){	/*미확인 물체 신호*/
			
		}else{	/**/

		}
	
	}

	server_close(socket_r2);
}
