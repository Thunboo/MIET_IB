#!/bin/bash

TARGET_DIR="/home/student/Labs/Lab_4/poems"
if ! [ $(pwd) = $TARGET_DIR ]; then
	cd $TARGET_DIR
	echo pwd is $(pwd)
fi

head -1 $(ls .) | cut -c 1-3 | sort | uniq -c | grep "\*\*\*" | awk '{print $1}'

