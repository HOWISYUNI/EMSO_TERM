MODULE="motor"
MAJOR=$(awk "\$2==\"$MODULE\" {print \$1}" /proc/devices)

mknod /dev/$MODULE c $MAJOR 0


MODULE="water_pump"
MAJOR=$(awk "\$2==\"$MODULE\" {print \$1}" /proc/devices)
mknod /dev/$MODULE c $MAJOR 0
