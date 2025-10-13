#!/bin/bash

TARGET_DIR="/home/student/Labs/Lab_4/poems"
if ! [ $(pwd) = $TARGET_DIR ]; then
	cd $TARGET_DIR
	echo pwd is $(pwd)
fi

ls -l | sed -n '1d;p'  | awk '{print $9, (/!/ ? "YES" : "NO")}'

