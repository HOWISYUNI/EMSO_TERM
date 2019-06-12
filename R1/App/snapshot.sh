#!/bin/bash
filename=$1
param=$#

if [ ${param} -eq 1 ]; then
    raspistill -o camera/${filename}.jpg
    echo snapshot saved ${filename}
fi
