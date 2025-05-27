SELECT * FROM employments;
SELECT * FROM graduates;
SELECT * FROM lessons;
SELECT * FROM professors;
SELECT * FROM school_cars;
SELECT * FROM students;
SELECT * FROM students_groups;

/*
 	№1
  	Выбрать ФИО всех студенток из всех нечетных групп, зачисленных после 31.12.2024
*/
SELECT last_name, first_name, patronymic --, enrollment_date
FROM students s
JOIN students_groups sg ON s.group_id = sg.group_id
WHERE last_name ~* '.*а$'
  AND s.group_id % 2 = 1
  AND enrollment_date > '31-12-2024';

/*
	№2
	Вывести всех студентов, чья почта не зарегистрированна на @gmail.com или mail.ru.
	Отсортировать по дате поступления (сначала новые, потом уже те, что раньше поступили),
	ФИО (По Возрастающей)
*/
SELECT last_name, first_name, patronymic, enrollment_date
FROM students s
JOIN students_groups sg ON s.group_id = sg.group_id
EXCEPT
SELECT last_name, first_name, patronymic, enrollment_date
FROM students s
JOIN students_groups sg ON s.group_id = sg.group_id
WHERE email ~* '.*@gmail.com'
   OR email ~* '.*@mail.ru'
ORDER BY 4 DESC, 1, 2, 3;

/*
	№3
	Вывести всех преподавателей с окладом >100.000. Отсортировать по Окладу по убывающей	
*/
SELECT last_name, first_name, patronymic, salary
FROM professors p
JOIN employments emp ON emp.professor_id = p.professor_id
WHERE salary > 100000::money
ORDER BY 4 DESC;

/*
	№4
	Вывести количество преподавателей к каждой "вилке" окладов с шагом 30000 рублей
*/
SELECT min_salary, max_salary, count(emp.*)
FROM employments emp 
RIGHT OUTER JOIN -- Чтобы даже если в данной "вилке" нету людей с тако зп - выводим диапазон
 (   VALUES (000000::money, 029999.99::money),
 			(030000::money, 059999.99::money),
 			(060000::money, 089999.99::money),
 			(090000::money, 119999.99::money),
 			(120000::money, 149999.99::money),
 			(150000::money, 179999.99::money)
 ) AS s (min_salary, max_salary)
 ON emp.salary BETWEEN s.min_salary AND s.max_salary
GROUP BY s.min_salary, s.max_salary
ORDER BY s.min_salary ASC;

/*
	№5
	Найти среднюю ЗП преподавателей НЕ УЧИТЫВАЯ 2 самые высокие и 2 самые низкие
*/
SELECT avg(nt.filtered_salary::numeric)::money AS "Средняя отфильтрованная ЗП"
FROM (
	SELECT emp.professor_id, emp.salary FROM employments emp
	EXCEPT (
		(SELECT emp1.professor_id, emp1.salary FROM employments emp1
		ORDER BY 1 ASC
		LIMIT 2)
		UNION
		(SELECT emp2.professor_id, emp2.salary from employments emp2
		ORDER BY 1 DESC
		LIMIT 2)
	)
) AS nt (filtered_professor_id, filtered_salary);

/*
	№6
	Вывести студентов, у которых ВНУТРИ имени почты содержится латинская букву A, 
	отсортировать по фамилиям в обратном порядке.
*/
SELECT last_name, first_name, patronymic, email
FROM students s
WHERE email ~* '.*a.*@.*'
ORDER BY 1 DESC;

/*
	№7
	Вывести всех преподавателей, у которых свыше 15 лет стажа 
	и при этом они трудоустроены до лета 2024 года.
*/
SELECT last_name, first_name, patronymic,
		experience_years, employed_since
FROM professors p 
LEFT JOIN employments emp ON emp.professor_id = p.professor_id
WHERE p.experience_years > 15
  AND emp.employed_since < '01-06-2024'::date
ORDER BY 4 DESC, 5, 1, 2, 3;

/*
	№8
	Вывести все групповые занятия (без повторений) с датой зачисления группы.
*/
SELECT DISTINCT lesson_id, lesson_type, professor_id, sg.group_id, enrollment_date
FROM lessons l
INNER JOIN students_groups sg ON sg.group_id = l.group_id;

/*
	№9
	Вывести всех преподавателей с ЗП выше средней по Автошколе.
	Первой строкой также вывести среднюю ЗП.
*/
select last_name, first_name, patronymic, salary
from (
(
	SELECT last_name, first_name, patronymic, salary, t
	FROM professors p
	JOIN employments e ON p.professor_id = e.professor_id
	CROSS JOIN (VALUES (2)) as sid (t)
	WHERE e.salary::numeric > (SELECT AVG(salary::numeric) FROM employments)
)
UNION 
(
	SELECT last_name, first_name, patronymic, temp_emp.salary, t
	FROM (
		SELECT AVG(emp.salary::numeric)::money AS "salary" FROM employments emp
	) as temp_emp (salary)
	CROSS JOIN (VALUES (1)) as sid (t)
	CROSS JOIN (VALUES ('-- Средняя'::varchar(30), 'Заработная'::varchar(30), 'Плата ='::varchar(30))) 
		as f (last_name, first_name, patronymic)
)
) as foo
ORDER BY t, salary ASC;

/*
	№10
	Вывести, сколько и каких занятий провел каждый преподаватель
*/
SELECT DISTINCT p.professor_id, p.last_name, p.first_name, p.patronymic, lesson_type, count(lesson_date) AS "Число занятий"
FROM professors p
CROSS JOIN lessons l
WHERE p.professor_id = l.professor_id
GROUP BY 1,2,3,4,5
ORDER BY lesson_type DESC, 1 ASC;

/*
	№11
	Студентов, прошедших как теорию, так и практику
*/
SELECT last_name, first_name, patronymic
FROM lessons l
LEFT JOIN students s ON s.student_id = l.student_id
GROUP BY 1,2,3
HAVING COUNT(DISTINCT lesson_type) = 2;

/*
	№12
	Всех выпускников, что не являются преподавателями в нашей Автошколе
*/
SELECT g.last_name, g.first_name, g.patronymic
FROM graduates g
EXCEPT --INTERSECT
SELECT p.last_name, p.first_name, p.patronymic
FROM professors p
ORDER BY 1,2,3;

/*
	№13
	Студентов, которым преподавал один и тот же профессор и теорию, и практику
*/
SELECT s.last_name, s.first_name, s.patronymic, professor_id
FROM lessons l
LEFT JOIN students s ON s.student_id = l.student_id
GROUP BY 1,2,3,4
HAVING count(distinct lesson_type) = 2;

/*
	№14
	Топ 3 самых частых учебных авто у студентов
*/
SELECT sc.brand, sc.model, COUNT(s.student_id) AS student_count
FROM school_cars sc
JOIN students s ON sc.car_plate = s.car_plate
GROUP BY sc.brand, sc.model
ORDER BY student_count DESC
LIMIT 3;

/*
	№15
	Вывести преподавателей, у которых было больше 5 практических занятий за май 2025 года
*/
SELECT p.professor_id, p.last_name, COUNT(DISTINCT l.lesson_date) --, lesson_date
FROM professors p
JOIN lessons l ON p.professor_id = l.professor_id
WHERE l.lesson_date BETWEEN '2025-05-01' AND '2025-05-31'
  AND l.lesson_type ~* 'практика'
GROUP BY p.professor_id, p.last_name
HAVING COUNT(DISTINCT l.lesson_date) > 5;

/*
	№16
	Вывести 3 студентов, у которых было большего всего практических занятий
	и 3 с наименьшим их числом
*/
SELECT * FROM (
(
	SELECT s.last_name, s.first_name, s.patronymic, count(*)
	FROM lessons l
	LEFT JOIN students s ON s.student_id = l.student_id
	WHERE lesson_type ~* 'практика'
	GROUP BY 1,2,3
	ORDER BY count DESC
	LIMIT 3
)
UNION
(
	SELECT s.last_name, s.first_name, s.patronymic, count(*)
	FROM lessons l
	LEFT JOIN students s ON s.student_id = l.student_id
	WHERE lesson_type ~* 'практика'
	GROUP BY 1,2,3
	ORDER BY count ASC
	LIMIT 3
) 
) as foo
ORDER BY count DESC;

/*
	№17
	Вывести все группы, в которых есть иностранные студенты (нету отчеств)
*/
SELECT DISTINCT group_id FROM students
WHERE patronymic IS NULL;

/*
	№18
	Вывести дату последнего практического занятия у каждого студента и количество этих занятий
*/
SELECT s.last_name, s.first_name, s.patronymic,
       MAX(l.lesson_date) AS "Дата последнего занятия",
       COUNT(*) AS "Число занятий"
FROM students s
JOIN lessons l ON s.student_id = l.student_id
WHERE lesson_type ~* 'практика'
GROUP BY s.student_id
ORDER  BY 1,2,3;

/*
	№19
	Вывести id студентов, что занимались с одним и тем же преподавателем 2 или более раз
*/
SELECT student_id, professor_id, COUNT(lesson_date)
FROM lessons
GROUP BY student_id, professor_id
HAVING COUNT(lesson_date) >= 2;

/*
	№20
	Вывести студентов, у которых занятия вёл хотя бы 1 из 3 преподавателей
	с самой большой ЗП
*/
SELECT s.last_name, s.first_name, s.patronymic
FROM students s
WHERE s.student_id IN (
	SELECT DISTINCT l.student_id FROM lessons l
	JOIN employments emp ON emp.professor_id = l.professor_id
	WHERE l.student_id = s.student_id
	   AND emp.salary IN (
			SELECT salary FROM employments
			ORDER BY salary DESC LIMIT 3
	  	   )
	);