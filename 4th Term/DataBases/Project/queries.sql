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