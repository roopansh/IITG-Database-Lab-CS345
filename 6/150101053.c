#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

const char DATABASE_NAME[] = "150101053_23feb2018";
void insert_ett(FILE *sqlFile);
void insert_cc(FILE *sqlFile);
void insert_cwsl(FILE *sqlFile);

int main(){
	FILE *sqlFile = fopen("load_data.sql", "w");
	if(sqlFile == NULL){
		printf("%s\n", "ERROR : Can't create 'load_data.sql'. Please Check");
		exit(1);
	}
	fprintf(sqlFile, "USE %s;\n\n", DATABASE_NAME);

	insert_cc(sqlFile);
	insert_ett(sqlFile);
	insert_cwsl(sqlFile);

	printf("%s\n", "Generated 'load_data.sql' successfully.");
	fclose(sqlFile);
    return 0;
}

void insert_ett(FILE *sqlFile){
	fprintf(sqlFile, "LOAD DATA LOCAL INFILE '%s' INTO TABLE ett FIELDS TERMINATED BY ',' LINES TERMINATED BY '\\n';\n\n", "database-19-jan-2018/database-19-jan-2018/exam-time-table.csv");
	return ;
}

void insert_cc(FILE *sqlFile){
	fprintf(sqlFile, "LOAD DATA LOCAL INFILE '%s' INTO TABLE cc FIELDS TERMINATED BY ',' LINES TERMINATED BY '\\n';\n\n", "database-19-jan-2018/database-19-jan-2018/course-credits.csv");

	return ;
}

void insert_cwsl(FILE *sqlFile){
	struct dirent *MainDirectoryReader, *SubDirectoryReader;
	DIR *SubDirectory, *MainDirectory;
	char BaseDir[200];

	strcpy(BaseDir, "database-19-jan-2018/database-19-jan-2018/course-wise-students-list/" );

	MainDirectory = opendir(BaseDir);
	if (MainDirectory == NULL){
		printf("Could not open Base Directory." );
		exit(1);
	}

	while ((MainDirectoryReader = readdir(MainDirectory)) != NULL){
		if (strcmp(MainDirectoryReader->d_name, ".") == 0 || strcmp(MainDirectoryReader->d_name, "..") == 0 ){
			continue;
		}

		char temp1[100];
		strcpy(temp1, BaseDir);

		SubDirectory = opendir(strcat(temp1, MainDirectoryReader->d_name));
		if (SubDirectory == NULL){
			printf("Could not open Sub Directory." );
			exit(1);
		}

		while ((SubDirectoryReader = readdir(SubDirectory)) != NULL){
			if (strcmp(SubDirectoryReader->d_name, ".") == 0 || strcmp(SubDirectoryReader->d_name, "..") == 0 ){
				continue;
			}

			char temp2[200];
			strcpy(temp2, temp1);
			strcat(temp2, "/");
			strcat(temp2, SubDirectoryReader->d_name);

			char *course = strtok(SubDirectoryReader->d_name, ".");

			fprintf(sqlFile, "LOAD DATA LOCAL INFILE '%s' INTO TABLE cwsl FIELDS TERMINATED BY ',' LINES TERMINATED BY '\\n' (@col1,@col2,@col3,@col4) set course_id='%s',serial_number=@col1, roll_number=@col2 ,name=@col3, email=@col4;\n\n", temp2, course);

			while (course != NULL)
			{
				course = strtok(NULL, ".");
			}
		}
		closedir(SubDirectory);

	}
	closedir(MainDirectory);
	return ;
}
