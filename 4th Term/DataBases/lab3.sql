-- Лабораторная работа №3
-- Иванов Иван
-- Вариант 6

-- Задание 2.1.
with count_degree AS (
	SELECT DISTINCT degree FROM professors
)
SELECT count(degree) FROM count_degree
--SELECT degree FROM count_degree
-- Не считает [null] ?

with count_degree AS (
	SELECT DISTINCT degree FROM professors
)
SELECT count(*) FROM count_degree

-- Задание 2.2.
-- 6, 16, 26, 36, 46, 56, 66, 76, 86
-- 1 INNER JOIN ; 2 LEFT JOIN ; 3 INTERSECT ?

-- 6 
-- Вывести номер трудового договора и название структурного подразделения,
-- к которому он относится. Отсортировать по номеру трудового договора.
SELECT e.contract_number, su.full_title
FROM employments e
LEFT JOIN structural_units su 
ON e.structural_unit_id = su.structural_unit_id
ORDER BY e.contract_number;

-- 16
-- Вывести ФИО каждого студента и срок действия его студенческого билета.
SELECT s.last_name, s.first_name, s.patronymic, 
	   sid.issue_date, sid.expiration_date,
	   age(sid.expiration_date, sid.issue_date) AS "Срок действия"
FROM students s
JOIN student_ids sid ON s.student_id = sid.student_id;

-- 26
-- Подсчитать количество каждой оценки («2», «3», «4», «5»), которые выставили
-- преподаватели. Вывести фамилию, имя, отчество преподавателя, наименование
-- дисциплины, оценку и ее количество. Исключить из вывода незаполненные поля
-- оценок. Отсортировать по фамилии, имени и дисциплине.
SELECT p.last_name, p.first_name, p.patronymic,
	   f.field_name,
	   fc.mark, count(fc.*)	   
FROM field_comprehensions fc
JOIN fields f ON fc.field = f.field_id
JOIN professors p ON f.professor_id = p.professor_id 
WHERE fc.mark IS DISTINCT FROM NULL --Documentation 9.2.

GROUP BY 1, 2, 3, 4, 5
ORDER BY p.last_name, p.first_name, f.field_name;

-- 36
-- Вывести фамилию, имя, номер студенческого и среднюю оценку студента по всем
-- дисциплинам исключая ‘Философию’. Отсортировать, по средней оценке, в порядке убывания.
SELECT s.last_name, 
	   s.first_name, 
	   s.student_id, 
	   CAST(avg(fc.mark) AS numeric(2,1)) as "Ср. оценка"
FROM students s
JOIN field_comprehensions fc ON s.student_id = fc.student_id
JOIN fields f ON fc.field = f.field_id
WHERE f.field_name != 'Философия' 
	AND fc.mark IS DISTINCT FROM NULL
GROUP BY 1, 2, 3
ORDER BY "Ср. оценка" DESC;

-- 46
-- Вывести ФИО всех студентов и форму их обучения
SELECT s.last_name, 
	   s.first_name, 
	   s.patronymic, 
	   sg.enrolment_status
FROM students s
LEFT JOIN students_groups sg 
ON s.students_group_number = sg.students_group_number ;

-- 56
-- Вывести названия всех групп, в последней строчке вывести: 
-- ‘Итого студентов' и количество всех студентов в институте.
SELECT DISTINCT s.students_group_number::text AS "Группы"
FROM students s
UNION
SELECT 'Итого студентов: ' || cast(count(*) as varchar(5)) AS "Группы"
FROM students
ORDER BY 1;

-- 66
-- Вывести имена студентов из первой и второй групп, количество этих имен,
-- столбец, содержащий значение 'первая' или ‘вторая' в зависимости от номера группы.
SELECT s1.first_name, '1' AS "group", count(*)
FROM students s1
WHERE (s1.students_group_number LIKE '%-_1%')
GROUP BY 1
UNION
SELECT s2.first_name, '2' AS "group", count(*)
FROM students s2
WHERE (s2.students_group_number LIKE '%-_2%')
GROUP BY 1
ORDER BY 1, 2;

-- 76
-- Вывести средний возраст студентов каждого структурного подразделения
SELECT nt.abbreviated_title, 
	   nt.full_title, 
	   AVG(age(CURRENT_DATE, nt.birthday))
FROM (
	SELECT s.birthday, su.abbreviated_title, su.full_title
	FROM students s
	LEFT JOIN students_groups sg
		ON s.students_group_number = sg.students_group_number
	LEFT JOIN structural_units su
		ON sg.structural_unit_id = su.structural_unit_id	
) nt
GROUP BY 1, 2
ORDER BY 3;

-- Аналогично: 
SELECT nt.abbreviated_title AS "Сокр. название", 
	   nt.full_title AS "Полное название", 
	   extract(year  from nt.avg) || ' лет ' ||
	   extract(month from nt.avg) || ' мес ' ||
	   extract(day   from nt.avg) || ' дней ' AS "Средний возраст студента"
FROM (
	SELECT su.abbreviated_title, 
		su.full_title,
		AVG(age(CURRENT_DATE, s.birthday))
	FROM students s
	LEFT JOIN students_groups sg
		ON s.students_group_number = sg.students_group_number
	LEFT JOIN structural_units su
		ON sg.structural_unit_id = su.structural_unit_id	
	GROUP BY 1, 2
	ORDER BY 2, 3
) nt;

-- 86
-- Вывести фамилию, имя и группу студентов, у которых троек больше, чем четверок.
SELECT last_name, first_name, students_group_number
FROM students s
WHERE (
	SELECT count(fc1.mark) AS "Cnt_3"
	FROM field_comprehensions fc1 
	WHERE s.student_id = fc1.student_id AND fc1.mark = '3'
	) > (
	SELECT count(fc2.mark) AS "Cnt_4"
	FROM field_comprehensions fc2
	WHERE s.student_id = fc2.student_id AND fc2.mark = '4'
	)
ORDER BY 1, 2, 3

-- 96
-- Вывести в одном столбце:
-- самое популярное имя среди студентов; 
-- фамилии всех студентов с этим именем.
SELECT "Фамилия" FROM (
SELECT s.last_name AS "Фамилия", temp_number 
FROM students s
CROSS JOIN ( VALUES (2)) AS t (temp_number)
WHERE s.first_name IN (
	SELECT s_.first_name FROM students s_
	GROUP BY 1
	ORDER BY count(*) DESC
	LIMIT 1
)
UNION
(
SELECT cast(('Самое популярное имя - ' || s_.first_name) as varchar(30)) AS "Фамилия", temp_number
FROM students s_
CROSS JOIN ( VALUES (1)) AS t (temp_number)
GROUP BY 1, 2
ORDER BY count(*) DESC
LIMIT 1
)
) as foo
ORDER BY temp_number, 1

-- Для проверки:
--SELECT s.last_name
--FROM students s
--WHERE s.first_name = 'Иван'

-------------------------------------------------------------------------------------------

-- INNER JOIN
-- Задание: Вывести код и оценки по БД самого старого студента
SELECT s.student_id AS "Код самого старого студента" , mark AS "Оценки по БД"
FROM students s
INNER JOIN field_comprehensions fc
	ON s.student_id = fc.student_id
INNER JOIN fields f
	ON f.field_id = fc.field
WHERE field_name = 'Базы данных'
	AND s.student_id = (
		SELECT student_id FROM students
		WHERE birthday = (SELECT min(birthday) FROM students)
		)
-- ! В БД - у каждого студента 1 / 0 (стоит NULL) оценка по БД


-- LEFT JOIN
-- Задание: Вывести всех преподавателей, предмет, что они ведут (если есть, иначе null)
SELECT last_name, first_name, patronymic, field_name FROM professors p
LEFT JOIN fields f ON p.professor_id = f.professor_id
ORDER BY 4 DESC, 1, 2, 3


-- INTERSECT
-- Задание: Вывести всех студентов, чьи фамилии начинаются на "И", кончаются на "ОВ"
SELECT last_name, first_name, student_id
FROM students
WHERE last_name ~ 'И.*'
INTERSECT
SELECT last_name, first_name, student_id
FROM students
WHERE last_name ~ '.*ов'


-- Доп. 3.10
SELECT DISTINCT last_name, first_name, students_group_number
, mark
, count(fc.mark) over (partition by s.student_id, fc.mark = 3)
, count(fc.mark) over (partition by s.student_id, fc.mark = 4)
FROM students s
RIGHT JOIN field_comprehensions fc ON s.student_id = fc.student_id
WHERE (
	SELECT count(fc1.mark) AS "Cnt_3"
	FROM field_comprehensions fc1 
	WHERE s.student_id = fc1.student_id AND fc1.mark = '3'
	) > (
	SELECT count(fc2.mark) AS "Cnt_4"
	FROM field_comprehensions fc2
	WHERE s.student_id = fc2.student_id AND fc2.mark = '4'
	)
	AND mark IN (3, 4)
ORDER BY 1, 2, 3, 4
