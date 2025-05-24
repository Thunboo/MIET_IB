-- Создаём таблицу для Учебных авто
CREATE TABLE school_cars (
    car_plate varchar(9) NOT NULL,
	brand varchar(30) NOT NULL,
	model varchar(30) NOT NULL,
    manufacture_year int,
	CONSTRAINT manufacture_year_check CHECK (manufacture_year > 1990 AND manufacture_year <= EXTRACT(year from CURRENT_DATE)::int)
);
ALTER TABLE ONLY school_cars
    ADD CONSTRAINT school_cars_pkey PRIMARY KEY (car_plate);
ALTER TABLE ONLY school_cars
	ADD CONSTRAINT school_cars_car_plate_check CHECK (car_plate ~* '^[АВЕКМНОРСТУХ]{1}[0-9]{3}[АВЕКМНОРСТУХ]{2}[0-9]{2,3}$');
 
-- Создаём таблицу для выпускников Автошколы
CREATE TABLE graduates (
    graduate_certificate_id varchar(20),
	last_name varchar(30) NOT NULL,
	first_name varchar(30) NOT NULL,
	patronymic varchar(30),
	graduation_date date NOT NULL
);
ALTER TABLE ONLY graduates
    ADD CONSTRAINT graduates_pkey PRIMARY KEY (graduate_certificate_id);
ALTER TABLE ONLY graduates
	ADD CONSTRAINT graduates_graduation_date_check CHECK (graduation_date < CURRENT_DATE + '1 days'::interval);
CREATE SEQUENCE graduates_certificate_seq;
	
-- Создаём таблицу Преподавателей и Инструкторов
CREATE TABLE professors (
    professor_id int NOT NULL,
	last_name varchar(30) NOT NULL,
	first_name varchar(30) NOT NULL,
	patronymic varchar(30),
    experience_years int NOT NULL,
	CONSTRAINT professors_experience_check CHECK (experience_years > 3)
);
ALTER TABLE ONLY professors
    ADD CONSTRAINT professors_pkey PRIMARY KEY (professor_id);

-- Создаём таблицу трудоустроств Преподавателей и Инструкторов
CREATE TABLE employments (
    professor_id int,
    employed_since date,
	salary money
);
ALTER TABLE ONLY employments
    ADD CONSTRAINT employments_pkey PRIMARY KEY (professor_id);
ALTER TABLE ONLY employments
    ADD CONSTRAINT employments_professor_id_fkey FOREIGN KEY (professor_id) REFERENCES professors(professor_id) ON DELETE CASCADE;
ALTER TABLE ONLY employments
	ADD CONSTRAINT employments_employed_since_check CHECK (employed_since < CURRENT_DATE + '15 days'::interval)

-- Создаём таблицу под группы учащихся
CREATE TABLE students_groups (
    group_id int NOT NULL,
    enrollment_date date DEFAULT CURRENT_DATE NOT NULL,
	graduation_date date DEFAULT (CURRENT_DATE + '3 months'::interval) NOT NULL
);
ALTER TABLE ONLY students_groups
    ADD CONSTRAINT students_groups_pkey PRIMARY KEY (group_id);
	
-- Создаём таблицу Учащихся
CREATE TABLE students (
    student_id int NOT NULL,
	last_name varchar(30) NOT NULL,
	first_name varchar(30) NOT NULL,
	patronymic varchar(30),
	group_id int NOT NULL,
	email varchar(30),
	inn varchar(12) DEFAULT '770000000000'::character varying,
    CONSTRAINT email_check CHECK (((email)::text ~* '^[A-Za-z0-9._+%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$'::text))
);
ALTER TABLE ONLY students
    ADD CONSTRAINT students_pkey PRIMARY KEY (student_id);
ALTER TABLE ONLY students
    ADD CONSTRAINT students_students_groups_fkey FOREIGN KEY (group_id) REFERENCES students_groups(group_id) ON DELETE CASCADE;
ALTER TABLE ONLY students
	ADD COLUMN IF NOT EXISTS car_plate varchar(9) NOT NULL DEFAULT 'О000ОО00';
ALTER TABLE ONLY students
	ADD CONSTRAINT students_cars_fkey FOREIGN KEY (car_plate) REFERENCES school_cars(car_plate) ON DELETE SET DEFAULT;

-- Создаём таблицу занятий (связь профессор-студент)
CREATE TABLE lessons (
    lesson_id SERIAL,
	lesson_type varchar(8),
    professor_id int,
    student_id int,
	group_id int,
	CONSTRAINT lessons_group_or_student CHECK ((student_id IS NOT NULL) OR (group_id IS NOT NULL)),
	CONSTRAINT lesson_type_check CHECK (lesson_type ~* '^Практика$' OR lesson_type ~* '^Теория$')
);
ALTER TABLE ONLY lessons
    ADD CONSTRAINT lessons_pkey PRIMARY KEY (lesson_id);
ALTER TABLE ONLY lessons
    ADD CONSTRAINT lessons_professor_id_fkey FOREIGN KEY (professor_id) REFERENCES professors(professor_id) ON DELETE CASCADE;
ALTER TABLE ONLY lessons
    ADD CONSTRAINT lessons_student_id_fkey FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE;
ALTER TABLE ONLY lessons
    ADD CONSTRAINT lessons_group_id_fkey FOREIGN KEY (group_id) REFERENCES students_groups(group_id) ON DELETE CASCADE;

CREATE OR REPLACE FUNCTION compute_certificate_id()
RETURNS TRIGGER
LANGUAGE PLPGSQL AS
$$
BEGIN
	IF NEW.graduation_date IS NULL
		THEN NEW.graduation_date = CURRENT_DATE; end if;
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