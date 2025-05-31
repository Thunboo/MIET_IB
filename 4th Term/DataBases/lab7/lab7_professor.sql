select * from students
where student_id= 873305;

select field_name, mark, semester, field from field_comprehensions
JOIN fields ON field = field_id
where student_id = 873305
  and (field_name ~* '.*опер.*систем.*'
  	or field_name ~* '.*баз.*данных.*'
	  )
order by 3;

BEGIN;
	UPDATE field_comprehensions
	SET mark = 2
	FROM fields
	WHERE field = field_id
	  AND student_id = 873305
  	  and (field_name ~* '.*опер.*систем.*'
  	       or field_name ~* '.*баз.*данных.*'
		  );
COMMIT;
--ROLLBACK;

BEGIN ISOLATION LEVEL Serializable;--Repeatable read; --Read committed;
	UPDATE field_comprehensions
	SET mark = 5
	FROM fields
	WHERE field = field_id
	  AND student_id = 873305
  	  and (field_name ~* '.*опер.*систем.*'
  	       or field_name ~* '.*баз.*данных.*'
		  );
COMMIT;

-- Isolation Level  | Before Commitment | After Commitment
-- Read uncommitted | 2, 2              | 5, 5
-- Read committed   | 2, 2              | 5, 5
-- Repeatable Read  | 2, 2              | 2, 2
-- Serializable     | 2, 2              | 2, 2