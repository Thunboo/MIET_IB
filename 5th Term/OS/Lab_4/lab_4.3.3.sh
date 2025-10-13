#!/bin/bash
if ! [ $1 ]; then
	echo "no filename was provided"
	exit 0
fi

TARGET_DIR="/home/student/Labs/Lab_4/poems"
if ! [ $(pwd) = $TARGET_DIR ]; then
	cd $TARGET_DIR
	echo pwd is $(pwd)
fi

if [ $2 ]; then
	NEW_FILE="new_lang_$1"
	echo $NEW_FILE
	sed -E 's/([а-яА-Я]+)/\1сла/g' $1 > $NEW_FILE
else
	sed -E 's/([а-яА-Я]+)/\1сла/g' $1
fi
