#!/bin/bash

#Find recursively in a given directory all the symbolic links, and report those that point to files/directories that no longer exist. Use operator -L to test if a path is a symbolic link, and operator -e to test if it exists (will return false if the target to which the link points does not exist)

LINKS=$(find $1 -type l)
for LINK in $LINKS
do
	if [ -L $LINK ] && [ ! -e $LINK ]
	then
		echo "$LINK nu este link simbolic"
	fi
done
