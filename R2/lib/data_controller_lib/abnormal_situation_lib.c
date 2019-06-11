

/*r1으로부터 비정상 상황 통신 대기*/
/*int wait_abnormal_situation_from_r1(){

	return 0;
}*/

/*r1으로부터 비정상 상황 데이터 수신*/
/*int recieve_abnormal_situation_from_r1(){

	return 0;
}*/

/*r3에 연결 요청*/
/*int request_connection_to_r3(){

	return 0;
}*/

/*비정상 상황 r3에 전송*/
int send_abnormal_situation_to_r3(){

	struct response rcv;

	rcv = request(socket, 'O', 'a', 's', len, data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}

}

/*비정상 상황시 알람 메시지*/
int alert_abnormal_situation(){
	/*비정상 상황 발생시 부저 울림*/
	printf("알람알람알람");
	return 0;
}
