from random import randint, choice
from os import getcwd
from datetime import datetime, timedelta

print(getcwd()) 

enr = ['01-04-2025', '22-04-2025', '13-05-2025']

lesson_types = ['Теория', 'Практика']
s_ids = list(range(1, 30 + 1))

num_of_lessons = 21 * 3 # => 210 записей. т.е. 

f = open('py_output.txt', 'w')
f.write('INSERT INTO lessons(lesson_type, professor_id, student_id, group_id, lesson_date)\nVALUES\n')
for i in range(num_of_lessons):
    if i % 21 == 0:
        p_id = randint(1, 20)
        group_id = randint(1, 3)
        date_str = (datetime.strptime(enr[group_id - 1], '%d-%m-%Y') + timedelta(days=14*(num_of_lessons // 21))).strftime('%d-%m-%Y')
        for j in range(1, 10 + 1):
            s = f'(\'{lesson_types[i % 21 != 0]}\', {p_id}, {(group_id - 1) * 10 + j}, {group_id}, \'{date_str}\')'
            # print(s, end = '')
            f.write(s)
            if not(i == num_of_lessons - 1 and j == 10):
                f.write(',\n') #; print(',')
            else:
                f.write(';') #; print(';')
    else:
        for j in range(3):
            s_id = choice(s_ids[j*10:(j + 1)*10])
            date_str = (datetime.strptime(enr[j], '%d-%m-%Y') + timedelta(days=(1 + i + j) )).strftime('%d-%m-%Y')
            s = f'(\'{lesson_types[i % 21 != 0]}\', {randint(1, 20)}, {s_id}, NULL, \'{date_str}\')'
            # print(s, end='')
            f.write(s)
            if not(i == num_of_lessons - 1 and j == 2):
                f.write(',\n') #; print(',')
            else:
                f.write(';') #; print(';')
f.close()