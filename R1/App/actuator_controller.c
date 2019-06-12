#include <stdio.h>
#include <unistd.h>

#include "app.h"

/* request <PUT>
> Usage  : R2.cmd_ctl.client->R1.act_ctl.server  
> method : 'U' (should be fixed)  
> type   : led_light('l'), led_alert('a'), buzzer('b')  
>           , camera('c'), motor('m'), water_pump('p'), sprinkler('s'),    
> cmd    : turn_on('1'), turn_off('0')  
> len    : data length  
> data   : timer(positive), infinit(zero), error(negative)
*/


/* response
> Usage  : Successful('s'), Failure('f'), Timeout('t')  
*/
int send_response(char type);


int main(void){
	int socket_r2;
	int fd;
	struct request rcv;

   	socket_r2 = server_open(R2_DATA_PORT);

	/*요청 대기*/
	while(1){
		rcv = wait_request(socket_r1);

		if(rcv.type == "l"){	/*빛 데이터*/
			
		}else if(rcv.type == "a"){	/*비상시 불빛 신호*/
			
		}else if(rcv.type == "b"){	/*비정상 버저 신호*/
			
		}else if(rcv.type == "c"){	/*카메라 신호*/
			
		}else if(rcv.type == "s"){	/*스프링 쿨러 신호*/
			
		}else{	/**/

		}
	
	}

	server_close(socket_r2);
}

int send_response(char type){
	struct response rsp;
	rsp.type = type;
	rsp.len = 0;
	strcpy(rsp.data, '\n');

	if(response(socket_r2, rsp.type, rsp.len, rsp.data)<0){
		return -1;
	}
	
	return 0;
}

