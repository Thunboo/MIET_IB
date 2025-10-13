#!/bin/bash

TARGET_DIR="/home/student/Labs/Lab_4/poems"
if ! [ $(pwd) = $TARGET_DIR ]; then
	cd $TARGET_DIR
	echo pwd is $(pwd)
fi
if [ -f "Hamlet.txt" ]; then
	#cat Hamlet.txt
	cat Hamlet.txt | sed -E 's/[^a-zA-Z ]//g' | tr 'A-Z' 'a-z' | tr -s ' ' '\n' | sort | uniq -c | sort -rn -k1 | head -1
# 1 все небуквы и не пробел - убрать
# 2 все буквы в нижний регистр
# 3 все последовательности пробелов заменить на перенос строки
# 4 без этого сорта работает не так
# 5 вывести все уникальные слова и их количество
# 6 сортировка в порядке по убыванию ЧИСЛА встреч слов
fi

