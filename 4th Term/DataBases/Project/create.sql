-- Создаём таблицу для Учебных авто
CREATE TABLE school_cars (
    car_plate varchar(9) NOT NULL,
	brand varchar(30) NOT NULL,
	model varchar(30) NOT NULL,
    manufacture_year int
);

-- Создаём таблицу для выпускников Автошколы
CREATE TABLE graduates (
    graduate_certificate_id varchar(20),
	last_name varchar(30) NOT NULL,
	first_name varchar(30) NOT NULL,
	patronymic varchar(30),
	graduation_date date NOT NULL
);
	
-- Создаём таблицу Преподавателей и Инструкторов
CREATE TABLE professors (
    professor_id int NOT NULL,
	last_name varchar(30) NOT NULL,
	first_name varchar(30) NOT NULL,
	patronymic varchar(30),
    experience_years int NOT NULL
);

-- Создаём таблицу трудоустроств Преподавателей и Инструкторов
CREATE TABLE employments (
    professor_id int,
    employed_since date,
	salary money
);

-- Создаём таблицу под группы учащихся
CREATE TABLE students_groups (
    group_id int, --NOT NULL,
    enrollment_date date DEFAULT CURRENT_DATE NOT NULL,
	graduation_date date DEFAULT (CURRENT_DATE + '3 months'::interval) NOT NULL
);
	
-- Создаём таблицу Учащихся
CREATE TABLE students (
    student_id int NOT NULL,
	last_name varchar(30) NOT NULL,
	first_name varchar(30) NOT NULL,
	patronymic varchar(30),
	group_id int DEFAULT NULL,
	car_plate varchar(9) NOT NULL DEFAULT 'О000ОО00',
	email varchar(30),
	inn varchar(12) DEFAULT '770000000000'::character varying
);

-- Создаём таблицу занятий (связь профессор-студент)
CREATE TABLE lessons (
	lesson_type varchar(8),
    professor_id int NOT NULL,
    student_id int NOT NULL,
	group_id int,
	lesson_date date DEFAULT CURRENT_DATE NOT NULL
);

-- Ограничения -------------------------------

-- school_cars
ALTER TABLE ONLY school_cars
    ADD CONSTRAINT school_cars_pkey PRIMARY KEY (car_plate);
ALTER TABLE ONLY school_cars
	ADD CONSTRAINT school_cars_car_plate_check CHECK (car_plate ~* '^[АВЕКМНОРСТУХ]{1}[0-9]{3}[АВЕКМНОРСТУХ]{2}[0-9]{2,3}$');
ALTER TABLE ONLY school_cars
	ADD CONSTRAINT school_cars_manufacture_year_check 
		CHECK (manufacture_year > 1990 AND manufacture_year <= EXTRACT(year from CURRENT_DATE)::int);
 
-- graduates
ALTER TABLE ONLY graduates
    ADD CONSTRAINT graduates_pkey PRIMARY KEY (graduate_certificate_id);
ALTER TABLE ONLY graduates
	ADD CONSTRAINT graduates_graduation_date_check CHECK (graduation_date < CURRENT_DATE + '1 days'::interval);
CREATE SEQUENCE graduates_certificate_seq;

-- professors
ALTER TABLE ONLY professors
    ADD CONSTRAINT professors_pkey PRIMARY KEY (professor_id);
ALTER TABLE ONLY professors
	ADD CONSTRAINT professors_experience_check CHECK (experience_years > 3);

-- employments
ALTER TABLE ONLY employments
    ADD CONSTRAINT employments_pkey PRIMARY KEY (professor_id);
ALTER TABLE ONLY employments
    ADD CONSTRAINT employments_professor_id_fkey FOREIGN KEY (professor_id) REFERENCES professors(professor_id) ON DELETE CASCADE;
ALTER TABLE ONLY employments
	ADD CONSTRAINT employments_employed_since_check CHECK (employed_since < CURRENT_DATE + '15 days'::interval);

-- students_groups
ALTER TABLE ONLY students_groups
    ADD CONSTRAINT students_groups_pkey PRIMARY KEY (group_id);

-- students
ALTER TABLE ONLY students
    ADD CONSTRAINT students_pkey PRIMARY KEY (student_id);
ALTER TABLE ONLY students
    ADD CONSTRAINT students_students_groups_fkey FOREIGN KEY (group_id) REFERENCES students_groups(group_id) ON DELETE SET DEFAULT;
ALTER TABLE ONLY students
	ADD CONSTRAINT students_cars_fkey FOREIGN KEY (car_plate) REFERENCES school_cars(car_plate) ON DELETE SET DEFAULT;
ALTER TABLE ONLY students
    ADD CONSTRAINT students_email_check CHECK ((email)::text ~* '^[A-Za-z0-9._+%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$'::text);

-- lessons
ALTER TABLE ONLY lessons
    ADD CONSTRAINT lessons_pkey PRIMARY KEY (student_id, group_id, lesson_date);
ALTER TABLE ONLY lessons
    ADD CONSTRAINT lessons_professor_id_fkey FOREIGN KEY (professor_id) REFERENCES professors(professor_id);-- ON DELETE CASCADE;
ALTER TABLE ONLY lessons
    ADD CONSTRAINT lessons_student_id_fkey FOREIGN KEY (student_id) REFERENCES students(student_id);-- ON DELETE CASCADE;
ALTER TABLE ONLY lessons
    ADD CONSTRAINT lessons_group_id_fkey FOREIGN KEY (group_id) REFERENCES students_groups(group_id);-- ON DELETE CASCADE;
ALTER TABLE ONLY lessons
	ADD CONSTRAINT lesson_type_check CHECK (lesson_type ~* '^Практика$' OR lesson_type ~* '^Теория$');
	
-- Триггеры, процедуры и функции ----------------------

CREATE OR REPLACE FUNCTION compute_certificate_id()
RETURNS TRIGGER
LANGUAGE PLPGSQL AS
$$
BEGIN
	IF NEW.graduation_date IS NULL
		THEN NEW.graduation_date = CURRENT_DATE; 
	END IF;
 	NEW.graduate_certificate_id := '777-' ||
		CURRENT_DATE || '-' || 
		LPAD(nextval('graduates_certificate_seq')::text, 5, '0');
 	RETURN NEW;
END;
$$;

CREATE OR REPLACE TRIGGER set_certificate_id 
BEFORE INSERT
ON graduates
FOR EACH ROW
EXECUTE FUNCTION compute_certificate_id();

----------------
CREATE OR REPLACE FUNCTION no_group_id()
RETURNS TRIGGER
LANGUAGE PLPGSQL AS
$$
BEGIN
	IF NEW.group_id IS NULL
		THEN NEW.group_id = -1; 
	END IF;
 	RETURN NEW;
END;
$$;

CREATE OR REPLACE TRIGGER no_group_id_given 
BEFORE INSERT
ON students_groups
FOR EACH ROW
EXECUTE FUNCTION no_group_id();

CREATE OR REPLACE TRIGGER no_group_id_given 
BEFORE INSERT
ON lessons
FOR EACH ROW
EXECUTE FUNCTION no_group_id();
----------------
CREATE OR REPLACE PROCEDURE no_empty_group_id()
LANGUAGE PLPGSQL AS
$$
BEGIN
	IF (SELECT count(*) FROM students_groups
		WHERE group_id = -1) = 0
		THEN INSERT INTO students_groups(group_id, enrollment_date, graduation_date)
		VALUES (-1, '01-01-2023', '01-01-2023'); 
	END IF;
END;
$$;

CALL no_empty_group_id();

CREATE OR REPLACE PROCEDURE delete_groups_except_empty()
LANGUAGE PLPGSQL AS
$$
BEGIN
	DELETE FROM students_groups;
	CALL no_empty_group_id(); 
END;
$$;

CREATE OR REPLACE FUNCTION dont_remove_empty_group_id_func() 
RETURNS TRIGGER
LANGUAGE PLPGSQL AS
$$
BEGIN
	CALL delete_groups_except_empty();
	RETURN NEW;
END;
$$;

CREATE OR REPLACE TRIGGER dont_remove_empty_group_id 
AFTER DELETE
ON students_groups
FOR EACH ROW
EXECUTE FUNCTION dont_remove_empty_group_id_func();