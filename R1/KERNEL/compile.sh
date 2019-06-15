#!bin/bash
cd ./ACTUATOR/buzzer/
make
make copy
make clean
cd ../led
make
make copy
make clean
cd ../led_alert
make
make copy
make clean
cd ../sprinkler
make
make copy
make clean
cd ../../SENSOR/dht11
make
make copy
make clean
cd ../light_sensor
make
make copy
make clean
cd ../pir
make
make copy
make clean
cd ../soil_sensor
make
make copy
make clean
cd ../ultrasonic
make
make copy
make clean

scp ./ACTUATOR/actuator_mknod.sh ./SENSOR/sensor_mknod.sh module_insert.sh module_remove.sh pi@10.10.10.13:~/ku_smart_farm/modules

