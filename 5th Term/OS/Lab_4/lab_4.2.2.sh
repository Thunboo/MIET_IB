#!/bin/bash

TARGET_DIR="/home/student/Labs/Lab_4/poems"
if ! [ $(pwd) = $TARGET_DIR ]; then
	cd $TARGET_DIR
	echo pwd is $(pwd)
fi
if [ -f "Hamlet.txt" ]; then
	#cat Hamlet.txt
	sed -E 's/\b[Gg][A-Za-z]*\b (.*)/MIET \1/g' ./Hamlet.txt  > ./Hamlet_edited.txt
fi
