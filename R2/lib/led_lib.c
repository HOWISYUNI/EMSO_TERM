

/*r3에서 led 작동여부를 위한 빛감지 센서 데이터를 위한 연결 요청*/
int reqeust_connection_to_r3(){

	return 0;
}

/*r3에서 led 작동여부를 위한 빛감지 센서 데이터를 수신 */
int recieve_light_data_from_r3(){

	return 0;
}

/*led 작동여부 판단*/
bool check_led(int data){
	int operation = false;
	/*light sensor값이 일정 수준 이하이면 led를 작동하는 것으로 판단*/
	if(data < 10){
		operation = true;
	}

	return operation;
}

/*r1에 연결 요청*/
int requset_connection_to_r1(){

	return 0;
}

/*led 작동여부 전송*/
void send_led_signal(bool sig){
	int socket;

	socket = client_init(src_ip, dest_ip, port, type);

	if(sig == true){
		request_put(socket, type, data, cmd);
	}else{
		/*보낼필요없음*/
	}

	return 0;
}

