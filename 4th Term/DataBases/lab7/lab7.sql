CREATE TABLE attendance (
	attendance_id SERIAL PRIMARY KEY,
	generated_code varchar(64),
	person_id integer,
	enter_time timestamp,
	exit_time timestamp,
	FOREIGN KEY (person_id) REFERENCES student_ids (student_id)
);

do
$$
DECLARE
	enter_time timestamp(0);
	exit_time timestamp(0);
	person_id integer;
	enter_id varchar(64);
BEGIN
	FOR i IN 1..1000000 LOOP
		--raise notice '%', i;
		enter_time := to_timestamp(random() * 
										(
											extract(epoch from '2023-12-31'::date) -
											extract(epoch from '2023-01-01'::date)
										)
										  + extract(epoch from '2023-01-01'::date)
										);
		exit_time := enter_time + (floor(random() * 36000 + 1) * '1 SECOND'::interval);

		person_id := (
							SELECT student_id FROM students
							ORDER BY random()
							LIMIT 1
					 	);
		enter_id := md5(random()::text);

		INSERT INTO attendance (generated_code, person_id, enter_time, exit_time)
		VALUES (enter_id, person_id, enter_time, exit_time);

		END LOOP;
END
$$;


do
$$
DECLARE
	enter_time timestamp(0);
	exit_time timestamp(0);
	person_id integer;
	enter_id varchar(64);
BEGIN
	enter_time := to_timestamp(random() * 
									(
										extract(epoch from '2023-12-31'::date) -
										extract(epoch from '2023-01-01'::date)
									)
									  + extract(epoch from '2023-01-01'::date)
									);
	exit_time := enter_time + (floor(random() * 36000 + 1) * '1 SECOND'::interval);
	person_id := (
						SELECT student_id FROM students
						ORDER BY random()
						LIMIT 1
				 	);
	enter_id := md5(random()::text);

	raise notice '% | % | % | %', enter_id, person_id, enter_time, exit_time;
--	INSERT INTO attendance (generated_code, person_id, enter_time, exit_time)
--	VALUES (enter_id, person_id, enter_time, exit_time);
END
$$;

CREATE INDEX ON attendance (generated_code ASC);

-- 2.1.1. ---------------------------------------------------------------
--        | Time before INDEXing Tb | Time after INDEXing Ta  | Ta / Tb |
-- SELECT | 2423,985 ms (00:02,424) | 1906,206 ms (00:01,906) | ~0,786  |
-- INSERT | 200,793 ms              | 3,891 ms                | ~0,019  |
-------------------------------------------------------------------------

select student_id from students order by random() limit 1;
CREATE INDEX ON attendance (person_id);

-- 2.1.2. ---------------------------------------------------------------
--        | Time before INDEXing Tb | Time after INDEXing Ta  | Ta / Tb |
-- SELECT | 1906,206 ms (00:01,906) | 1786,255 ms (00:01,786) | ~0,937  |
-- SELECT |                         |                         |         |
-- +WHERE |   59,566 ms             |   18,51 ms              | ~0,311  |
-------------------------------------------------------------------------

-- 2.1.3.
select * 
from attendance
where generated_code ~ '.*a$'
order by generated_code;
-- without order by ~ 0.8 secs
-- with    order by ~ 0.5 secs

-- 2.3.
CREATE INDEX ON field_comprehensions (student_id ASC);
-- Потому что порой среди полутысячи студентов нам нужны оценки лишь одного.
-- А оценок всего порядка 25000, поэтому поиск по данной таблице затрудён.
-- Данный индекс ускоряет поиск оценок каждого отдельного студента.