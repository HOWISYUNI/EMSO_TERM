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
void send_response(char type);
static int socket_r2;

int main(void){
	
	struct request rcv;
	int time;

   	socket_r2 = server_open(R2_DATA_PORT);


	/*요청 대기*/
	while(1){
		int ret = wait_request(socket_r2,&rcv);

		if(rcv.type == 'l'){	/*광합성용 LED */
			if(rcv.cmd == '1'){
				time=atoi(rcv.data);
				if(time>0){
					if(turn_on_led_timer(time)<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					}
				}
				else if(time==0){
					if(turn_on_led()<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					}
				}
				else{
					/*Error*/
					send_response('f');
				}
			}
			else if(rcv.cmd == '0'){
				if(turn_off_led()<0){
					/*Error*/
					send_response('f');						
				}else{
					send_response('s');
				}
			}
			else{
				/*Error*/
				send_response('f');
			}
		}else if(rcv.type == 'a'){	/*비상시 불빛 신호*/
			if(rcv.cmd == '1'){
				time=atoi(rcv.data);
				if(time>0){
					if(turn_on_led_alert_timer(time)<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					}
				}
				else if(time==0){
					if(turn_on_led_alert()<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					}
				}
				else{
					/*Error*/
					send_response('f');
				}
			}
			else if(rcv.cmd == '0'){
				if(turn_off_led_alert()<0){
					/*Error*/
					send_response('f');						
				}else{
					send_response('s');
				}
			}
			else{
				/*Error*/
				send_response('f');
			}
		}else if(rcv.type == 'b'){	/*비정상 버저 신호*/
			if(rcv.cmd == '1'){
				time=atoi(rcv.data);
				if(time>0){
					if(turn_on_buzzer_timer(time)<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					}
				}
				else if(time==0){
					if(turn_on_buzzer()<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					}
				}
				else{
					/*Error*/
					send_response('f');
				}
			}
			else if(rcv.cmd == '0'){
				if(turn_off_buzzer<0){
					/*Error*/
					send_response('f');						
				}else{
					send_response('s');
				}
			}
			else{
				/*Error*/
				send_response('f');
			}
		}else if(rcv.type == 'c'){	/*카메라 신호*/
			if(snapshot<0){
				/*Error*/	
				send_response('f');
			}else{
				send_response('s');
			}
/*****************이거 FTP 방식 고려할 생각 있는지 한번 고민해보셈******************/
			
		}else if(rcv.type == 's'){	/*스프링 쿨러 신호*/
			if(rcv.cmd == '1'){
				time=atoi(rcv.data);
				if(time>0){
					
				}
				else if(time==0){
					
				}
				else{
					/*Error*/
				}
			}
			else if(rcv.cmd == '0'){
				
			}
			else{
				/*Error*/
			}
		}else{	/**/

		}
	
	}

	server_close(socket_r2);
}

void send_response(char type){
	struct response rsp;
	rsp.type = type;
	rsp.len = 0;
	strcpy(rsp.data, "\n");

	if(response(socket_r2, rsp.type, rsp.len, rsp.data)<0){
		/*Error*/
	}
	
	
}



