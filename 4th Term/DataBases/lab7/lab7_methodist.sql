select * from students
where student_id= 873305;

select field_name, mark, semester from field_comprehensions
JOIN fields ON field = field_id
where student_id = 873305
order by 3;

BEGIN ISOLATION LEVEL Serializable; --Repeatable read; --Read committed;
select field_name, mark, semester from field_comprehensions
JOIN fields ON field = field_id
where student_id = 873305
  and (field_name ~* '.*опер.*систем.*'
  	or field_name ~* '.*баз.*данных.*'
	  )
order by 3;
ROLLBACK;