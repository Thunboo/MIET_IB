CREATE ROLE "driving_school_manager" WITH
	LOGIN
	CREATEDB
	CONNECTION LIMIT -1
	PASSWORD '5up3r_p4ssW0rd';

GRANT USAGE ON SCHEMA public TO "driving_school_manager";
GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA public TO "driving_school_manager";
   
ALTER SCHEMA public OWNER TO "driving_school_manager";
   
