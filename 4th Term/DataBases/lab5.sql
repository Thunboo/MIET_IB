-- Лабораторная работа №5
-- Иванов Иван
-- Вариант 6

--select substring(inn from 1 for 3)::bigint / 100 
--from students

-- 2.1. Поставьте “!” перед фамилией студента, у которого долгов более 12

CREATE TABLE debtor_students
(
    id SERIAL PRIMARY KEY,
    last_name VARCHAR(30) NOT NULL,
    first_name VARCHAR(30) NOT NULL,
    patronymic VARCHAR(30) NULL,
	student_id integer NOT NULL,
    students_group_number VARCHAR(7) NOT NULL,
    debt_number INTEGER NOT NULL
);

-- DROP TABLE debtor_students;

INSERT INTO debtor_students (last_name, first_name, patronymic,
							  student_id, students_group_number, debt_number)
(
        SELECT last_name, first_name, patronymic, 
			   students.student_id, students_group_number, COUNT(*) AS "Number of debts" 
        FROM students
        INNER JOIN field_comprehensions ON 
            field_comprehensions.student_id = students.student_id
        WHERE field_comprehensions.mark = 2
        GROUP BY 1,2,3,4,5
);

UPDATE students s
SET last_name = '!' || s.last_name
FROM debtor_students ds 
WHERE debt_number > 12 and s.student_id = ds.student_id;

--UPDATE students SET last_name = substring(last_name from 2)

--2.2. Автоматически заполните поле «ИНН» в формате, 
--    заданном в предыдущей лабораторной работе 
--    (XXXXAAAAAABB, где все указанные символы – цифры).
--    XXXX – за код налогового органа возьмите год рождения студента, 
--    следующие шесть цифр (AAAAAA) – номер студенческого билета. 
--    Две последние контрольные цифры вычислите по правилу:
--        Вычислить 1-ю контрольную цифру:
--    •  Вычислить сумму произведений цифр ИНН (с 1-й по 10-ю) 
--      на следующие коэффициенты — 7, 2, 4, 10, 3, 5, 9, 4, 6, 8 
--      (т.е. 7 * ИНН[1] + 2 * ИНН[2] + ...).
--    •  Вычислить младший разряд остатка от деления полученной суммы на 11.
--        Вычислить 2-ю контрольную цифру:
--    •  Вычислить сумму произведений цифр ИНН (с 1-й по 11-ю) 
--      на следующие коэффициенты — 3, 7, 2, 4, 10, 3, 5, 9, 4, 6, 8 
--      (т.е. 3 * ИНН[1] + 7 * ИНН[2] + ...).
--    •  Вычислить младший разряд остатка от деления полученной суммы на 11.

UPDATE students s 
SET INN = (EXTRACT(YEAR from s.birthday)::bigint * 100000000
    + s.student_id::bigint * 100)::varchar(12);

-- XXXX_AAAAAA_BB
UPDATE students s
SET inn = (inn::bigint
    + ( (
              (inn::bigint / 100000000000) % 10 * 7 +
              (inn::bigint / 10000000000 ) % 10 * 2 +
              (inn::bigint / 1000000000  ) % 10 * 4 +
              (inn::bigint / 100000000   ) % 10 * 10 +
              (inn::bigint / 10000000    ) % 10 * 3 +
              (inn::bigint / 1000000     ) % 10 * 5 +
              (inn::bigint / 100000      ) % 10 * 9 +
              (inn::bigint / 10000       ) % 10 * 4 +
              (inn::bigint / 1000        ) % 10 * 6 +
              (inn::bigint / 100         ) % 10 * 8
             ) / 11 ) % 10 * 10)::varchar(12);
UPDATE students s
SET inn = (inn::bigint
    + ( (
             (inn::bigint / 100000000000) % 10 * 3 +
             (inn::bigint / 10000000000 ) % 10 * 7 +
             (inn::bigint / 1000000000  ) % 10 * 2 +
             (inn::bigint / 100000000   ) % 10 * 4 +
             (inn::bigint / 10000000    ) % 10 * 10 +
             (inn::bigint / 1000000     ) % 10 * 3 +
             (inn::bigint / 100000      ) % 10 * 5 +
             (inn::bigint / 10000       ) % 10 * 9 +
             (inn::bigint / 1000        ) % 10 * 4 +
             (inn::bigint / 100         ) % 10 * 6 +
             (inn::bigint / 10          ) % 10 * 8
            ) / 11 ) % 10 )::varchar(12);

-- 2.3.
INSERT INTO sick_leave_list (student_id, certificate_id, since, till)
values
	(820611, 1000, '2024-11-05', '2024-11-08'),
	(866735, 1001, '2024-11-09', '2024-11-16'),
	(829651, 1002, '2024-12-28', '2025-01-01'),
	(852471, 1003, '2024-11-21', '2024-11-22'),
	(870446, 1004, '2025-01-07', '2025-01-14'),
	(819225, 1005, '2025-01-26', '2025-01-28'),
	(878202, 1006, '2025-02-11', '2025-02-14'),
	(840132, 1007, '2025-02-19', '2025-02-23'),
	(863719, 1008, '2025-03-13', '2025-03-16'),
	(890704, 1009, '2025-03-21', '2025-03-26');

INSERT INTO doctors (doctor_id, last_name, first_name, patronymic)
values
	(7016784, 'Фёдоров', 'Иван', 'Александрович'),
	(7040575, 'Петрова', 'Екатерина', 'Алексеевна'),
	(7030742, 'Кузнецов', 'Дмитрий', 'Артёмович'),
	(7035636, 'Попова', 'Ирина', 'Евгеньевна'),
	(7060105, 'Петров', 'Сергей', 'Артёмович'),
	(7004102, 'Морозова', 'Ольга', 'Сергеевна'),
	(7074455, 'Фёдоров', 'Максим', 'Владимирович'),
	(7092651, 'Петрова', 'Елена', 'Владимировна'),
	(7007426, 'Соколов', 'Алексей', 'Александрович'),
	(7077408, 'Соколова', 'Юлия', 'Владимировна');

INSERT INTO doctor_to_leave_list (doctor_id, certificate_id)
values
	(7016784, 1000),
	(7040575, 1001),
	(7030742, 1002),
	(7035636, 1003),
	(7060105, 1004),
	(7004102, 1005),
	(7074455, 1006),
	(7092651, 1007),
	(7007426, 1008),
	(7077408, 1009);

-- TEST
select sll.student_id, s.last_name, s.first_name, since, till, 
		ds.doctor_id, ds.last_name, ds.first_name, ds.patronymic
from sick_leave_list sll
join doctor_to_leave_list dtll on sll.certificate_id = dtll.certificate_id
join doctors ds on ds.doctor_id = dtll.doctor_id
join students s on s.student_id = sll.student_id;