from random import randint, choice
from os import getcwd

print(getcwd())


lesson_types = ['Теория', 'Практика']
s_ids = list(range(1, 30 + 1))

num_of_lessons = 21 * 3 # => 210 записей. т.е. 

f = open('py_output.txt', 'w')
f.write('INSERT INTO lessons(lesson_type, professor_id, student_id, group_id)\nVALUES\n')
for i in range(num_of_lessons):
    if i % 21 == 0:
        p_id = randint(1, 20)
        group_id = randint(1, 3)
        for j in range(1, 10 + 1):
            s = f'(\'{lesson_types[i % 21 != 0]}\', {p_id}, {(group_id - 1) * 10 + j}, {group_id})'
            # print(s, end = '')
            f.write(s)
            if not(i == num_of_lessons - 1 and j == 10):
                f.write(',\n') #; print(',')
            else:
                f.write(';') #; print(';')
    else:
        for j in range(3):
            s = f'(\'{lesson_types[i % 21 != 0]}\', {randint(1, 20)}, {choice(s_ids[j*10:(j + 1)*10])}, NULL)'
            # print(s, end='')
            f.write(s)
            if not(i == num_of_lessons - 1 and j == 2):
                f.write(',\n') #; print(',')
            else:
                f.write(';') #; print(';')
f.close()