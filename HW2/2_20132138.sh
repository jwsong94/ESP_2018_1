#!/bin/bash

# 20132138
# Jungwoo Song
# Github - https://github.com/jwsong94/ESP_2018_1

PORT=$1
GPIODIR="gpio$PORT"

echo "gpio : $PORT"

cd /sys/class/gpio/

echo $PORT > ./export
cd $GPIODIR

echo out > direction

i=1
while [ $i -le 10 ]
do
    echo "LED ON"
    echo 1 > value
    sleep 1s
    echo "LED OFF"
    echo 0 > value
    sleep 1s

    let "i = i + 1"
done

cd ..
echo 13 > unexport
