-- Лабораторная работа №2
-- Иванов Иван
-- Вариант 6

-- Задание 2.1. Исследование типов данных
DO
$$
DECLARE
	summ real :=0.0;     --Diff : -992
	--summ numeric := 0.0; --Diff : 0.00
	--summ money := 0.0;   --Diff 0,00 ₽
BEGIN
FOR i IN 1..100000 LOOP
	summ := summ + 999.99; --::money;
END LOOP;
RAISE NOTICE 'Summ = %;', summ;
RAISE NOTICE 'Diff = %;', 99999000.00 - summ; --::money - summ;
END
$$ language plpgsql;

-- Задание 2.2. Написание запросов на языке SQL
-- 6, 16, 26, 36, 46, 56, 66, 76
-- 6
SELECT email FROM students
	WHERE first_name = 'Кирилл'
	ORDER BY birthday ASC;

-- 16
SELECT last_name, first_name, patronymic --, birthday
FROM students
-- 23.08 till 21.11
WHERE (extract(month from birthday) = 8  AND extract(day from birthday)  >= 23)
   OR (extract(month from birthday) > 8  AND extract(month from birthday) < 11)
   OR (extract(month from birthday) = 11 AND extract(day from birthday)  <= 21)
ORDER BY 1 ASC; 

-- 26
SELECT * FROM professors;
SELECT degree, count(*)
FROM professors
GROUP BY degree
HAVING count(*) > 2
ORDER BY count ASC;

-- 36
SELECT extract(day from birthday) AS day, count(*)
FROM students
GROUP BY day
HAVING count(*) < 15
ORDER BY day ASC;

-- 46
SELECT *
FROM students
WHERE email ~ '^[A-G]'
ORDER BY student_id ASC;

-- 56
SELECT students_group_number, count(*)
FROM students
WHERE  (students_group_number LIKE '%-3%') AND (last_name !~ 'а$')
GROUP BY students_group_number;

-- 66
SELECT last_name AS "Фамилия", students_group_number AS "Группа"
FROM students
WHERE  ((students_group_number LIKE '%-2%')
	 OR (students_group_number LIKE '%-4%'))
	 AND (students_group_number NOT LIKE '%В')
ORDER BY last_name DESC;

-- 76
SELECT professor_id as "Код", count(*) AS "Число читаемых дисциплин"
FROM fields
WHERE professor_id BETWEEN 810000 AND 850000
GROUP BY professor_id
HAVING count(*) > 1
ORDER BY "Число читаемых дисциплин" DESC;

-- Больше требуемого:
SELECT p.last_name AS "Фамилия", 
	   p.first_name AS "Имя", 
	   p.patronymic AS "Отчество",
	   f.professor_id AS "Код",
	   count(*) AS "Число читаемых дисциплин"
FROM fields f
JOIN professors p ON p.professor_id = f.professor_id
GROUP BY 1, 2, 3, 4
HAVING count(*) > 1
ORDER BY "Число читаемых дисциплин" DESC;

-------------------------------------------------------------------------------------------

-- 1
-- Вывести ФИО, номер студенческих билетов студентов группы ИБ-21,
-- отсортировав по фамилиям в обратном алфавитном порядке
SELECT first_name, last_name, patronymic, student_id
FROM students
WHERE students_group_number = 'ИБ-21'
ORDER BY last_name DESC

-- 2
-- Вывести фамилии студентов, имеющих тройки
SELECT DISTINCT last_name FROM students s
RIGHT JOIN field_comprehensions fc ON s.student_id = fc.student_id
WHERE mark = 3
ORDER BY 1

-- 3
-- Вывести среднюю оценку, которую ставит каждый преподаватель. Отсортировать по оценкам (наив->наим)
SELECT last_name, first_name, patronymic, ROUND(AVG(mark), 2)
FROM professors p
RIGHT JOIN fields f ON p.professor_id = f.professor_id
RIGHT JOIN field_comprehensions fc ON f.field_id = fc.field
GROUP BY 1, 2, 3
ORDER BY 4 DESC

-- 4
-- Подсчитать количество разных имён у студентов. Вывести лишь те, которых > 5
SELECT first_name, COUNT(*)
FROM students
GROUP BY 1
HAVING COUNT(*) > 5
ORDER BY 2 DESC

-- 5
-- Вывести всех студенток, чьи отчества кончаются на 'ровна'
SELECT last_name, first_name, patronymic
FROM students
WHERE patronymic ~ '.*ровна'

-- 6
-- Вывести всех студентов однофамильцев, родившихся в 2005-2006
SELECT last_name, first_name, patronymic
FROM (
	SELECT last_name, first_name, patronymic, birthday,
	count(last_name) over (partition by last_name) as last_name_count
FROM students
) as foo
WHERE last_name_count > 1
  AND birthday::text ~ '200[56].*'

-- 7
-- Вывести 5 преподавателей с самой большой ставкой
SELECT last_name, first_name, patronymic, wage_rate
FROM professors p JOIN employments e ON p.professor_id = e.professor_id
ORDER BY 4 DESC
LIMIT 5

-- Доп 2.5
SELECT su.structural_unit_id, sg.students_group_number
,	ROW_NUMBER() over (partition by su.structural_unit_id)
FROM structural_units su
RIGHT JOIN students_groups sg ON su.structural_unit_id = sg.structural_unit_id
ORDER BY 1, 3