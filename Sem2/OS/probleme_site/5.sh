#!/bin/bash

#	Write a script that receives dangerous program names as command line arguments. The script will monitor all the processes in the system, and whenever a program known to be dangerous is run, the script will kill it and display a message.

for proc in $@
do
	found=$(ps | grep -E "$proc")
	if [ ! -z $found ]
	then
		pid=$(echo $found | awk '{print $1}')
		kill -9 $pid
		echo "Procesul $proc a fost incheiat!"
	fi
	sleep 1
done
