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
static int c_socket;

int main(void){
	
	struct request rcv;
	int time;

	socket_r2 = server_open(9999);

	if(socket_r2 < 0){
		printf("fail open server\n");
		return 0;
	}
	/*요청 대기*/
	while(1){
		c_socket = wait_request(socket_r2,&rcv);
		if(c_socket < 0){
			printf("fail receive request\n");
			return 0;
		}
		if(rcv.type == 'l'){	/*광합성용 LED */
printf("[LED] type\n");
			if(rcv.cmd == '1'){
				time=atoi(rcv.data);
				if(time>0){
printf("[LED] %d만큼 ON\n",time);
					if(turn_on_led_timer(time)<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					}
				}
				else if(time==0){
printf("[LED] ON\n");
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
printf("[LED] OFF\n");
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
printf("[ALERT_LED] type\n");
			if(rcv.cmd == '1'){
				time=atoi(rcv.data);
				if(time>0){
printf("[ALERT_LED] %d만큼 ON\n",time);
					if(turn_on_led_alert_timer(time)<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					}
				}
				else if(time==0){
printf("[ALERT_LED] ON\n");
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
printf("[ALERT_LED] OFF\n");
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
printf("[BUZZER] type\n");
			if(rcv.cmd == '1'){
				time=atoi(rcv.data);
				if(time>0){
printf("[BUZZER] %d만큼 ON\n",time);
					if(turn_on_buzzer_timer(time)<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					}
				}else if(time==0){
printf("[BUZZER] ON\n");
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
printf("[BUZZER] OFF\n");
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
printf("[CAMERA] type \n");
			if(snapshot<0){
				/*Error*/	
				send_response('f');
			}else{
				send_response('s');
			}
/*****************이거 FTP 방식 고려할 생각 있는지 한번 고민해보셈******************/
			
		}else if(rcv.type == 's'){	/*스프링 쿨러 신호*/
printf("[SPRINKLER] type\n");
			if(rcv.cmd == '1'){
				time=atoi(rcv.data);
				if(time>0){
printf("[SPRINKLER] %d만큼 ON\n",time);
					if(timer_sprinkler(time)<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					
					}
				}
				else if(time==0){
printf("[SPRINKLER] ON\n");
					if(turn_on_sprinkler()<0){
						/*Error*/
						send_response('f');						
					}else{
						send_response('s');
					
					}
					
				}
				else{
					/*Error*/
				}
			}
			else if(rcv.cmd == '0'){
printf("[SPRINKLER] OFF\n");
				if(turn_off_sprinkler()<0){
					/*Error*/
					send_response('f');						
				}else{
					send_response('s');
				
				}
				
			}
			else{
				/*Error*/
			}
		}else{	/**/
printf("[이상한 값] type\n");

		}
	
	}

	server_close(socket_r2);
}

void send_response(char type){
	struct response rsp;
	rsp.type = type;
	rsp.len = 0;
	strcpy(rsp.data, "\n");

	if(response(c_socket, rsp.type, rsp.len, rsp.data)<0){
		/*Error*/
	}
	
	
}



