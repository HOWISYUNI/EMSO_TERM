
/*r3에 연결 요청*/
int request_connection_to_r3(){

	return 0;
}

/*r3에 온습도 데이터 요청*/
int request_humidity_data_to_r3(){

	return 0;
}

/*r3로부터 온습도 데이터 수신 대기*/
int wait_humidity_data_from_r3(){

	return 0;
}

/*r3로부터 온습도 데이터 수신*/
int recieve_humidity_data_from_r3(){

	return 0;
}

/*스프링클러 작동여부 판단*/
bool check_sprinkler(struct response res){
	bool operation = false;

	/*습도 데이터가 일정 수준 이하이면 스프링클러를 작동신호를 출력*/
	if( (res.type == 's') && (res.data < 20) ){
		operation = true;
	}	

	return operation;
}

/*r1에 연결 요청*/
int reqeust_connection_to_r1(){
	
	return 0;
}

/*스프링클러 제어 신호 전송*/
void send_sprinkler_signal(int socket, bool sig){

	if(sig == true){
		request(socket, 'U', 's', '1', len, data);
	}else{
		/*보낼필요없음*/
	}

}
