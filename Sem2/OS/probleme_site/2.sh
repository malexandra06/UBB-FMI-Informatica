#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Numar insuficient de argumente"
	echo "Utilizare: $0 dir"
	exit 1
elif [ ! -d $1 ]
then
	echo "$1 nu este director!"
	exit 2
fi

FILES=$(find $1 -type f -name '*.c')
COUNT=0
for FILE in $FILES
do
	NR=$(wc -l $FILE | awk '{print $1}')
	if [ $NR -gt 500 ]
	then
		echo "$FILE"
		COUNT=$((COUNT+1))
	fi
	if [ $COUNT -eq 2 ]
	then
		break
	fi	
done
exit 0
