#!bin/bash
cd ./SENSOR/dht11
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
cd ../../
scp ./SENSOR/sensor_mknod.sh module_insert.sh module_remove.sh pi@10.10.10.13:~/ku_smart_farm/modules

