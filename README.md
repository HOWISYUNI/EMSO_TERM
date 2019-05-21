
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
__최종 시연__ : 기말고사 기간(6/17예상 혹은 그 다음 주)
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
* 
---
## Member
> 201311276 박형민   
> 201311287 엄현식  
> 2013 이진호   
> 2013 한예훈   
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
	1. __토양 온습도 센서__
	2. 온습도 센서
	3. 빛 감지 센서
	4. LED
	5. 적외선 센서
	6. 거리 감지 센서
3. Device
	1. 모터
	2. 부저
	3. 카메라

---
## Development Tool
1. Remote Repository
2. Project management
3. 

---
## Development Directory Structure
```
Smart Farm System
 ├──R1/
 │   ├──Kernel/
 │   │	   ├──SF_NET/
 │   │	   │    └──NETWORK.c 		/* Smart From Network */
 │   │	   ├──SENSOR/
 │   │	   │    ├──SENSOR_1.c
 │   │	   │    ├──SENSOR_2.c
 │   │	   │    ├──SENSOR_3.c
 │   │	   │    └──SENSOR_4.c
 │   │	   └──DEVICE/
 │   │            ├──DEVICE_1.c
 │   │            ├──DEVICE_2.c
 │   │            └──DEVICE_3.c
 │   ├──lib/							
 │   │	  ├──SF_NET/
 │   │	  │    └──NETWORK_LIB.c 
 │   │	  ├──SENSOR/
 │   │	  │    └──SENSOR_LIB.c
 │   │	  └──DEVICE/
 │   │	       └──DEVICE_LIB.c
 │   └──App/
 │       ├──daemon.c 			/* Background */
 │       └──SF_SUBCTR.c 		/* sub Controller */
 │
 ├──R2/
 │   ├──Kernel/
 │   │   └──SF_NET/
 │   │        └──NETWORK.c
 │   ├──lib/
 │   │	 └──SF_NET/
 │   │	      └──NETWORK_LIB.c 
 │   └──App/
 │	 ├──daemon.c	 		/* Background */
 │       ├──SF_CTR.c 			/* Controller */
 │       └──SF_UIF.c 			/* User Interface */
 │
 └──R3/
     ├──Kernel/
     │   └──SF_NET/
     │        └──NETWORK.c
     ├──lib/
     │   └──SF_NET/
     │	      └──NETWORK_LIB.c 
     └──App/
     	 ├──daemon.c 			/* Background */
         └──SF_STORAGE.c 		/* Storage */
```
