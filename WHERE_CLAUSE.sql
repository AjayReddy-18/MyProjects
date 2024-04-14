-- SQL SELECT queries with WHERE clause to fetch records

-- SQL query to fetch one record 
SELECT * FROM Item WHERE ItemId = "I1001";

-- SQL query to fetch few records
SELECT * FROM Item WHERE UnitPrice > 499;

--  SQL query to fetch all records
SELECT * FROM Item WHERE (1=1);

-- SQL query to fetch no records
SELECT * FROM Item WHERE (1=0);