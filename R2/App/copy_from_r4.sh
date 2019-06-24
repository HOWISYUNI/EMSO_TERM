#!/bin/bash
filename=$1
param=$#

if [ ${param} -eq 1 ]; then
    scp pi@10.10.10.16:~/ku_smart_farm/camera/${filename}.jpg ./camera
    echo snapshot saved ${filename}.jpg in /camera
fi
