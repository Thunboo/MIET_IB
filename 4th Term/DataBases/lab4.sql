CREATE TABLE field_to_prof (
	field_id uuid NOT NULL UNIQUE,
	professor_id INTEGER NOT NULL,

	CONSTRAINT field_fk
		FOREIGN KEY(field_id)
		REFERENCES fields(field_id),
	CONSTRAINT professor_id_fk
		FOREIGN KEY(professor_id)
		REFERENCES professors(professor_id)
);

--ALTER TABLE students
--ADD COLUMN snils varchar(13) DEFAULT '000-000-000 0'
--CONSTRAINT snils_format
--	CHECK (snils ~* '^[0-9]{3}-[0-9]{3}-[0-9]{3} [0-9]');

-- ALTER TABLE students DROP COLUMN snils; 

-- XXNNAAAAAABB, XX - код субъекта РФ
ALTER TABLE students
ADD COLUMN inn varchar(12) DEFAULT '770000000000'
CONSTRAINT inn_format
	CHECK (inn ~* '^(77|69|05|39|32)[0-9]{10}');

ALTER TABLE students
DROP CONSTRAINT inn_format;

ALTER TABLE students
ADD CONSTRAINT inn_format
	CHECK (inn ~* '^(77|69|05|19|20)[0-9]{10}');

-- ALTER TABLE students DROP COLUMN inn;