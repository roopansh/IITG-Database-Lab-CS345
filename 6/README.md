### HOW TO

		$ gcc 150101053.c -o load_data

		$ ./load_data

		$ mysql -u root -p

		mysql> source 150101053.sql;
		mysql> source load_data.sql;
		mysql> source 150101053_tt_violation.sql;
		mysql> source 150101053_count_credits.sql;

		mysql> call tt_violation();
		mysql> call count_credits();
