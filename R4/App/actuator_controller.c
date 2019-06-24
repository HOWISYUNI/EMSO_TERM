#include "actuator_controller.h"


int main(void){
    int ret;
    int sock, c_sock;
	/* request from R2.commandController */
	struct request req;
	struct response rsp;

    /* Server socket */
	sock = server_open(R4_ACT_PORT);

	if(sock < 0){
		printf("fail open server\n");
		return 0;
	}
	
	/* wait request forever */
	while(1){
	    /* Return Client Socket when receive Request Successful */
		c_sock = wait_request(sock, &req);

		if(c_sock < 0){
			printf("fail receive request\n");
			break;
		}
		
		if(req.type == 'l')
		    ret = led_controller(req);
		else if(req.type == 'a')
            ret = led_alert_controller(req);
		else if(req.type == 'b')
			ret = buzzer_controller(req);
		else if(req.type == 'c')
		    ret = camera_controller(req);
		else if(req.type == 's')
		    ret = sprinkler_controller(req);
		else if(req.type == 'e')
		    ret = emergency_controller();
	    else if(req.type == 'f')
	        ret = fin_emgcy_controller();
		else
		    ret = -1;
		
		if(ret < 0){
		    printf("fail act Control\n");
		    rsp.type = 'f';
		    rsp.len = 0;
        	strcpy(rsp.data, "\0");
		}
		else{
		    printf("success act Control\n");
		    rsp.type = 's';
		    rsp.len = 0;
		    strcpy(rsp.data, "\0");
		}
		
		ret = response(c_sock, rsp.type, rsp.len, rsp.data);
		if(ret < 0)
		    printf("fail send response\n");
		else
		    printf("success send repsonse\n");
	}

	server_close(sock);
}

/* type = l : LED CONTROL SIGNAL */
int led_controller(struct request req){
    int time = 0;
    int ret;
    
    /* cmd == 1 : ON */
	if(req.cmd == '1'){
		time = atoi(req.data);
		/* data > 0 : TIMER */
		if(time > 0)
		    ret = turn_on_led_timer(time);
		/* data == 0 : INFINITE */
		else if(time == 0)
		    ret = turn_on_led();
		/* data < 0 : ERROR */
		else
			ret = -1;
	}
	/* cmd == 0 : OFF */
	else if(req.cmd == '0')
	    ret = turn_off_led();

	/* cmd != 0 && cmd != 1 : ERROR */
	else
		ret = -1;

    /* RETURN RESULT */
    if(ret < 0)
        return -1;
        
    return 0;
}

/* type = a : LED ALERT CONTROL SIGNAL */
int led_alert_controller(struct request req){
    int time = 0;
    int ret;
    
    /* cmd == 1 : ON */
    if(req.cmd == '1'){
	    time = atoi(req.data);
	    if(time > 0)
	        ret = turn_on_led_alert_timer(time);
	    else if(time == 0)
	        ret = turn_on_led_alert();						
	    else
		    ret = -1;
    }
    
	/* cmd == 0 : OFF */
    else if(req.cmd == '0')
        ret = turn_off_led_alert();
        
    /* cmd != 0 && cmd != 1 : ERROR */
    else
        ret = -1;
    
    /* RETURN RESULT */
    if(ret < 0)
        return -1;

	return 0;
}

/* type = b : BUZZER CONTROL SIGNAL */
int buzzer_controller(struct request req){
    int time = 0;
    int ret;
    
    /* cmd == 1 : ON */
    if(req.cmd == '1'){
	    time = atoi(req.data);
	    if(time > 0)
	        ret = turn_on_buzzer_timer(time);
	    else if(time == 0)
	        ret = turn_on_buzzer();						
	    else
		    ret = -1;
    }
    
	/* cmd == 0 : OFF */
    else if(req.cmd == '0'){
        ret = turn_off_buzzer();
    }
    
    /* cmd != 0 && cmd != 1 : ERROR */
    else
        ret = -1;
        
    /* RETURN RESULT */
    if(ret < 0)
        return -1;

	return 0;
}

/* type = c : CAMERA CONTROL SIGNAL */
int camera_controller(struct request req){
    int ret;
    
    /* cmd == 1 : SNAPSHOT */
    if(req.cmd == '1'){
        /* request.data ==> FILE_NAME */
        ret = snapshot(req.data);
        if(ret < 0)
            return -1;
    }
    /* cmd != 1 : ERROR */
    else
        return -1;
        
    return 0;
}

/* type = s : SPRINKLER CONTROL SIGNAL */
int sprinkler_controller(struct request req){
    int time = 0;
    int ret;
    
    /* cmd == 1 : ON */
    if(req.cmd == '1'){
	    time = atoi(req.data);
	    if(time > 0)
	        ret = timer_sprinkler(time);
	    else if(time == 0)
	        ret = turn_on_sprinkler();						
	    else
		    ret = -1;
    }
    
	/* cmd == 0 : OFF */
    else if(req.cmd == '0')
        ret = turn_off_sprinkler();
        
    /* cmd != 0 && cmd != 1 : ERROR */
    else
        ret = -1;
    
    /* RETURN RESULT */
    if(ret < 0)
        return -1;

	return 0;
}

int emergency_controller(){
    int ret;
    int failed;
    
    /* LED AELRT ON */
    ret = turn_on_led_alert_timer(0);
    if(ret < 0)
        failed = -1;
        
    /* BUZZER ON */
    ret = turn_on_buzzer_timer(0);
    if(ret < 0)
        failed = -1;
        
    /* camera on */
    ret = snapshot("timelog");
    if(ret < 0)
        failed = -1;
        
    if(failed == -1)
        return -1;
    
    return 0;
}

int fin_emgcy_controller(){
    int ret;
    int failed;
    
    /* LED AELRT OFF */
    ret = turn_off_led_alert_timer(0);
    if(ret < 0)
        failed = -1;
        
    /* BUZZER OFF */
    ret = turn_off_buzzer_timer(0);
    if(ret < 0)
        failed = -1;

    if(failed == -1)
        return -1;
    
    return 0;
}
