#!/bin/bash

if [ -f "./$1" ]; then
#if [ $1 ]; then
	echo "renaming $1"
	RESULT=`(echo "$1 $(date +%R)" | tr "." " " | sed -E 's/(.*) (.*) (.*)/\1\,\3\,BGD\.\2/g')`
	#echo $RESULT
	mv ./$1 ./$RESULT
	ls -l | grep $RESULT
fi
