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
if [ -f $1 ]; then
	head -1 $1 | awk '{for(i=1; i <=NF; i++) {L+=length($i)+1}} END {for(i=1; i<L+2; i++) {printf "-"}} END {printf "\n|"} END {printf "%s", $0} END {printf "|\n"} END {for(i=1; i<L+2; i++) {printf "-"}} END {printf "\n"}'
fi
