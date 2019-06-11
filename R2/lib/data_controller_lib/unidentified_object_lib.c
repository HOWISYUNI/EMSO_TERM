#include "./unidentified_object_lib.h"

/* 미확인 물체 접근 데이터 통신 대기
 * Caller : R2.DataController 
 * Description : R1으로부터 request 대기
 * request : 미확인 물체가 접근하고 있으니, 관리자에게 알람 및 기록 요청 
 */
/*int wait_unidentified_object_from_r1(){

	return 0;
}*/

/*미확인 물체 접근 데이터 수신*/
/*int recieve_unidentified_object_from_r1(){
	/*  */
	return 0;
}*/

/*r3에 연결 요청*/
/*int request_connection_to_r3(){

	return 0;
}*/

/*r3에 미확인 물체 데이터 전송*/
void send_unidentified_object_to_r3(int socket){
	struct response rcv;

	rcv = request(socket, 'O', 'a', 's', len, data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}

	return 0;
}


