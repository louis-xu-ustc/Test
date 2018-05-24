#!/bin/bash

while [ : ]
do
    echo "send hello world! to localhost"
    echo -n "hello world!" > /dev/udp/localhost/50101
    sleep 1 
done
