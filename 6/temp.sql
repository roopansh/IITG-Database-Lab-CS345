USE 150101053_23feb2018;

CREATE DEFINER = 'root'@'localhost' PROCEDURE account_count()
  SELECT 'Number of accounts:', COUNT(*) FROM mysql.user;
END
