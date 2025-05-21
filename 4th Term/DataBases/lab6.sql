-- Лабораторная работа №6
-- Иванов Иван
-- Вариант 6

-- 2.1.
SELECT student_id FROM students ORDER BY random() LIMIT 1;

-- 853801
do
$$
DECLARE
	mark_ptr int;
	sid int := 853801;
	var float := 0;
	amount int := 0;
BEGIN
	--SELECT student_id INTO sid FROM students 
	--ORDER BY random() LIMIT 1;
	
	FOR mark_ptr IN SELECT mark 
		FROM field_comprehensions
		WHERE student_id = sid
	loop
		if mark_ptr IS NOT NULL then
			var = var + mark_ptr;
			amount = amount + 1;
		end if;
	end loop;
	raise notice '% AVG mark : %/% = %', sid, var, amount, var/amount;
END
$$;

SELECT student_id, AVG(mark) 
FROM field_comprehensions
WHERE student_id = 853801 
GROUP BY 1;
-- PL/pgSQL  - 5,278 ms
-- SQL-Query - 1,714 ms

-- 2.2.
-- 6
-- Напишите скрипт, выводящий ФИО студента и его пол.
select * from students 
where last_name ~ '.*а$' or patronymic ~ '.*на$' 
order by patronymic;

do
$$
DECLARE
	stud record;
	pp int := 0;
BEGIN
	for stud in SELECT last_name, first_name, patronymic
		FROM students
	loop
		pp = pp + 1;
		if stud.patronymic ~ '.*на$' or stud.last_name ~ '.*а$' then
			raise notice '%) ФИО - % % % | Пол - Ж',
			pp, stud.last_name, stud.first_name, stud.patronymic;
		else
			raise notice '%) ФИО - % % % | Пол - М',
			pp, stud.last_name, stud.first_name, stud.patronymic;
		end if;
	end loop;
END
$$;

-- 16
-- Напишите скрипт, генерирующий случайное местоположение каждого студента
--на карте (его координаты в градусах). Определите материк, соответствующий
--этим координатам. Считайте, попаданием на материк, если координаты лежат в
--пределах:
--Европа – между 1° с.ш. и 77° с.ш. и между 9° з.д. и 67° в.д.
--Африка – между 37° с.ш. и 34° ю.ш. и между 13° з.д. и 51° в.д.
--Австралия – между 10° ю.ш. и 39° ю.ш. и между 113° в.д. и 153° в.д.
--Северная Америка – между 7° с.ш. и 71° с.ш. и между 55° з.д. и 168° з.д.
--Южная Америка – между 12° с.ш. и 53° ю.ш. и между 34° з.д. и 81° з.д.
--Антарктида– ниже 63° ю.ш.

do
$$
DECLARE
	x int;
	y int; --random() * 180 - 90;
	stud record;
BEGIN
	for stud in SELECT student_id FROM students
	loop
		x = random() * 180 - 90;
		y = random() * 180 - 90;

		if (x between 1 and 77) and (y between -9 and 67) then
			raise notice '% - Европа', stud.student_id;
		elsif (x between -34 and 37) and (y between -13 and 51) then
			raise notice '% - Африка', stud.student_id;
		elsif (x between -39 and -10) and (y between 113 and 153) then
			raise notice '% - Австралия', stud.student_id;
		elsif (x between 7 and 71) and (y between -168 and -55) then
			raise notice '% - Северная Америка', stud.student_id;
		elsif (x between -53 and 12) and (y between -81 and -34) then
			raise notice '% - Южная Америка', stud.student_id;
		elsif x < -63 then	
			raise notice '% - Антарктида', stud.student_id;
		else
			raise notice '% - Утонул', stud.student_id;
		end if;
	end loop;
END
$$;

-- 26
-- Создайте процедуру увеличивающую на один бал оценку студентов именинников
-- по определенной дисциплине. Входной параметр - название дисциплины
CREATE PROCEDURE birthday_bonus(param_field varchar(100))
LANGUAGE SQL
AS
$$
	UPDATE field_comprehensions SET mark = mark + 1
	FROM students, fields
	WHERE students.student_id = field_comprehensions.student_id
	  AND field_comprehensions.field = fields.field_id
	  AND field_name = param_field
	  AND mark < 5
	  AND EXTRACT(day   from current_date) = EXTRACT(day   from students.birthday)
	  AND EXTRACT(month from current_date) = EXTRACT(month from students.birthday)
$$;

CALL birthday_bonus('WEB-дизайн');

select * from students
where EXTRACT(day   from current_date) = EXTRACT(day   from students.birthday)
  AND EXTRACT(month from current_date) = EXTRACT(month from students.birthday)
-- 865571
select student_id, field_name, mark from field_comprehensions
JOIN fields on field_id = field
where student_id = 865571 and field_name = 'WEB-дизайн'; -- mark < 5 order by mark desc

-- 36
-- Создайте функцию, рассчитывающую моду оценки у конкретного студента
CREATE OR REPLACE FUNCTION temp_smc(s_id integer) RETURNS TABLE (mark integer, n integer)
LANGUAGE SQL
AS $$
	SELECT mark, n 
	FROM (
		SELECT student_id, mark, count(*) as n
		FROM field_comprehensions
		GROUP BY 1, 2
		ORDER BY 1, 2 DESC
	) as foo (student_id, mark, n)
	WHERE student_id = s_id;
$$;

CREATE OR REPLACE FUNCTION retrieve_max_cnt(s_id integer) RETURNS integer
LANGUAGE SQL AS $$ SELECT max(n) FROM temp_smc(s_id); $$;

CREATE OR REPLACE FUNCTION mode_mark(param_sid integer) RETURNS float
LANGUAGE SQL
AS 
$$
	SELECT avg(mark)
	FROM temp_smc(param_sid) t
	LEFT JOIN (values (retrieve_max_cnt(param_sid), 1)) AS v (v1, v2) ON n = v1
	WHERE v1 IS NOT NULL
$$;

do
$$
DECLARE
	stud record;
BEGIN
	for stud in SELECT student_id FROM students
	loop
		raise notice '%) mode mark = %',
			stud.student_id, mode_mark(stud.student_id);
	end loop;
END	
$$;

-- 46
-- Создайте функцию, вычисляющую число преподавателей в каждом структурном подразделении.
CREATE OR REPLACE FUNCTION prof_per_SU(param_suid integer) RETURNS integer
LANGUAGE SQL AS $$
	
	SELECT count(*) --ps.professor_id, su.structural_unit_id, su.full_title
	FROM professors ps
	JOIN employments es ON ps.professor_id = es.professor_id
	JOIN structural_units su ON es.structural_unit_id = su.structural_unit_id
	WHERE su.structural_unit_id = param_suid
$$;

do
$$
DECLARE
	su record;
BEGIN
	for su in select structural_unit_id, full_title from structural_units
	loop
		raise notice '% Professors in %', prof_per_SU(su.structural_unit_id), su.full_title; 
	end loop;
END
$$;

-- 56
-- Создайте триггер, выводящий сообщение об изменении оценок у студентов.
-- Сообщение должно содержать id студента, старую и новую оценку.
CREATE OR REPLACE FUNCTION mark_change_log()
RETURNS TRIGGER
LANGUAGE PLPGSQL AS
$$
BEGIN
  IF NEW.mark <> OLD.mark THEN
    raise notice 'student % mark changed from % to %',
    NEW.student_id, OLD.mark, NEW.mark;
  END IF;
  RETURN NEW;
END;
$$;

CREATE OR REPLACE TRIGGER mark_change 
AFTER UPDATE
ON field_comprehensions
FOR EACH ROW
EXECUTE FUNCTION mark_change_log();

UPDATE field_comprehensions SET mark = 3
FROM fields
WHERE fields.field_name = 'Иностранный язык'
  AND fields.field_id = field_comprehensions.field
  AND field_comprehensions.student_id = 847516;

 select * from field_comprehensions fc
 JOIN fields f on fc.field = f.field_id
 where student_id = 847516 and mark = 3;
-- 66
-- Если ЗП =0 => удалить преподавателя
CREATE OR REPLACE FUNCTION wage_fire_func()
RETURNS TRIGGER
LANGUAGE PLPGSQL AS
$$
BEGIN
	IF NEW.salary = 0 THEN
		DELETE FROM professors
  		WHERE professor_id = NEW.professor_id;
	END IF;
	RETURN NEW;
END;
$$;

CREATE OR REPLACE TRIGGER wage_fire
AFTER UPDATE
ON professors
FOR EACH ROW 
EXECUTE PROCEDURE wage_fire_func();

-- 2.3
CREATE OR REPLACE FUNCTION new_sick_notice()
RETURNS TRIGGER
LANGUAGE PLPGSQL AS
$$
BEGIN
  raise notice '% has left sick', student_id;
END;
$$;

CREATE OR REPLACE TRIGGER new_sick
AFTER INSERT
ON sick_leave_list
EXECUTE FUNCTION new_sick_notice();