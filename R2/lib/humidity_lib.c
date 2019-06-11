/*토양 온습도임 헷갈리면 차후 수정하겠음*/
/*r1 통신 대기*/
int wait_humidity_data_from_r1(){

	return 0;
}

/*r1으로부터 데이터 수신*/
int recieve_humidity_data_from_r1(){

	return 0;
}

/*r3에 연결 요청*/
int request_connection_to_r3(){

	return 0;
}

/*r3에 온습도데이터 전달*/
void send_humidity_data_to_r3(int socket){

	struct response rcv;

	rcv = request_post(socket, type, data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}


}
