#!/bin/bash

#Find recursively in a directory, all the files with the extension ".log" and sort their lines (replace the original file with the sorted content).

FILES=$(find $1 -type f -name '*.log')
for FILE in $FILES
do
	sort $FILE -o $FILE
	echo "$FILE a fost sortat"
done
