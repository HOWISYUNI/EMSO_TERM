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

scp ./ACTUATOR/actuator_mknod.sh module_insert.sh module_remove.sh pi@10.10.10.16:~/ku_smart_farm/modules

