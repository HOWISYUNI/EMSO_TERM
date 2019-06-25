
# Smart Farm System
### DeadLine
__중간 발표 자료 제출__ : 6/2(SUN)
__중간 발표__ : 6/5 - 6/7(WED, FRI)
```
발표 주제
SCENARIO & GOAL & Internal Design & Excellence & Plan
평가 요소
Creativity & Technological Challenging & Completeness
```
__최종 시연__ : 6/25(TUE) 13:30PM
```
Goal Achievement
Stability of demonstration
Completeness of device drivers
 - Does it use more than three different kinds of sensors/actuators? 
 - Are new sensors controlled by WiringPi or own drivers? 
Peer review ( 리더십, 토론 능력, 책임감, 전공능력 )
```
---
## Overview
* 임베디드 시스템 소프트웨어 팀 프로젝트
* Smart Farm System (스마트 팜 시스템)

---
## Member
> 201311276 박형민   
> 201311287 엄현식  
> 201311306 이진호   
> 201311320 한예훈   
---
## KU Smart Farm
> [Demonstrate Link](https://youtu.be/uXOjjKhMu4A)
### Scenario 1
> 빛 조도 분석  
> 광합성에 도움을 주는 파장의 LED 작동 여부 결정  
> 지속적인 광합성 환경 지원  
### Scenario 2
> 토양 온습도 분석  
> SPRINKLER 작동 여부 결정  
> 지속적인 수분 공급  
### Scenario 3
> 물체 감지  
> 물체 접근 감지  
> 일정 임계치 이상으로 다가올 경우 비상 알림 시스템 작동  
### Scenario 4
> 대기 중 온도 감지  
> 비정상 수치 감지시 비상 알림 시스템 작동  
### User interface 
> .중앙 제어 모듈(R2)에서 사용  
> R3(Storage & Refine Controller)로부터 환경 데이터 정보 요청  
> R4(Actuator Controller)로부터 Actuator 작동 제어 요청  
---
## Environments
### Development Environment
OS : Linux  
Editor : Text Editor, vim, ..  

### Execution Environment
OS : Rasbian

### Devices Specification
1. Raspi
2. Sensor
	1. 토양 온습도 센서  
	2. 온습도 센서  
	3. 빛 감지 센서  
	4. PIR 센서  
	5. 거리 감지 센서  
3. Actuator
	1. 모터  
	2. 부저  
	3. 카메라  
	4. 워터 펌프  
	5. LED / ALERT LED  
### Coding Style
가이드라인 : [kernel_code_style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html)

#### 1. 들여쓰기 : __space 4__

#### 2. 함수 정의
```
/* 함수 이름 : 함수 기능
 * 인자값 설명
 * 반환값 설명
 * * /
function() {
}
```

#### 3. 한 줄짜리
```if() break;```


#### 4. 주석
```/*  */```

#### 5. Naming

__변수명__ : ```val_name;```

__함수명__ : ```func_name_like_that() ```

__구조체명__ :```typedef struct_t {} name;```

__매크로__ : ```DEFINE_SOMETHING```


---
## Development Tool
1. Remote Repository : github
2. Project management : None
3. Communitcation : Slack

---
## Development Directory Structure
```
Smart Farm System
 ├──R1/
 │   ├──Kernel/
 │   │	   ├──SENSOR/
 │   │	   │    ├──SENSOR_1.c
 │   │	   │    ├──SENSOR_2.c
 │   │	   │    ├──SENSOR_3.c
 │   │	   │    ├──SENSOR_4.c
 │   │	   │    └──SENSOR_5.c
 │   ├──lib/							
 │   │	   └──SENSOR/
 │   │	       └──SENSOR_LIB.c
 │   └──App/
 │       └──SNSR_CTRL.c 		/* Sensor Controller */
 │
 ├──R2/
 │   ├──lib/
 │   │   └──CTRL_LIB.c 			/* Controller library */
 │   └──App/
 │       ├──DATA_CTRL.c 		/* Data Controller */
 │       ├──CMD_CTRL.c 			/* Refine Controller */
 │       └──UI_CTRL.c 			/* User Interface */
 │
 ├──R3/
 │   ├──lib/
 │   │   └──CTRL_LIB.c 			/* Controller library */
 │   └──App/
 │   	 ├──STG_CTRL.c 			/* Storage Controller */
 │       └──RFN_CTRL.c 			/* Refine Controller */
 ├──R4/
 │   ├──Kernel/
 │   │	   └──ACTUATOR/
 │   │            ├──ACTUATOR_1.c
 │   │            ├──ACTUATOR_2.c
 │   │            └──ACTUATOR_3.c
 │   ├──lib/							
 │   │	  └──ACTUATOR/
 │   │	       └──ACTUATOR_LIB.c
 │   └──App/
 │        └──ACT_CTRL.c 			/* Actuator Controller */
 └──KSF_NET/
     └──NETWORK_LIB.c 
```
