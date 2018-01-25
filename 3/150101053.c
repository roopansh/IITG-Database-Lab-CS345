#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char DATABASE_NAME[] = "25jan2018";

void insert_ett();
void insert_cc();
void insert_cwsl();


int main(){

	insert_ett();
	insert_cc();
	insert_cwsl();

    return 0;
}


/*
insert into ett(course_id, exam_date, starttime, endtime)
values ('cs345', '2018-02-25' , '09:00' , '11:00');
*/
void insert_ett(){
	FILE *sqlFile, *fp;
	char courseID[10], date[20], startTime[10], endTime[10];

	printf("%s\n", "\nGenerating '150101053_ett.sql'");
	sqlFile = fopen("150101053_ett.sql", "w");
	if(sqlFile == NULL){
		printf("%s\n", "ERROR : Can't create '150101053_ett.sql'. Please Check");
		exit(1);
	}

	fprintf(sqlFile, "USE %s;\n", DATABASE_NAME);

	printf("%s\n", "Reading the Time Table.");
	fp = fopen("database-19-jan-2018/exam-time-table.csv", "r");
	if(fp == NULL){
		printf("Error opening 'database-19-jan-2018/exam-time-table.csv' file.\n");
		exit(1);
	}

	while(fscanf(fp, "%[^,], %[^,], %[^,], %[^\n]\n", courseID, date, startTime, endTime) != -1){
		// printf("%s %s %s %s\n", courseID, date, startTime, endTime);
		fprintf(sqlFile, "INSERT INTO ett(course_id, exam_date, starttime, endtime) VALUES('%s', '%s', '%s', '%s');\n", courseID, date, startTime, endTime);
		fprintf(sqlFile, "INSERT INTO ett_temp(course_id, exam_date, starttime, endtime) VALUES('%s', '%s', '%s', '%s');\n", courseID, date, startTime, endTime);
		fprintf(sqlFile, "INSERT INTO ett_clone(course_id, exam_date, starttime, endtime) VALUES('%s', '%s', '%s', '%s');\n", courseID, date, startTime, endTime);
	}

	fclose(fp);
	fclose(sqlFile);
	printf("%s\n", "Time Table data read successfully and SQL file generated.");

	return ;
}


/*
insert into cc(course_id, number_of_credits)
    values ('CS345', 3);
*/
void insert_cc(){
	FILE *sqlFile, *fp;
	char courseID[10];
	int credits;

	printf("%s\n", "\nGenerating '150101053_cc.sql'");
	sqlFile = fopen("150101053_cc.sql", "w");
	if(sqlFile == NULL){
		printf("%s\n", "ERROR : Can't create '150101053_cc.sql'. Please Check");
		exit(1);
	}
	fprintf(sqlFile, "USE %s;\n", DATABASE_NAME);

	printf("%s\n", "Reading the Course Credits.");
	// Course Credits
	fp = fopen("database-19-jan-2018/course-credits.csv", "r");
	if(fp == NULL){
		printf("Error opening 'database-19-jan-2018/course-credits.csv' file.\n");
		exit(1);
	}

	while(fscanf(fp, "%[^,],%d\n", courseID, &credits) != -1){
		// printf("%s %d\n", courseID, credits);
		fprintf(sqlFile, "INSERT INTO cc(course_id, number_of_credits) VALUES ('%s', %d);\n", courseID, credits);
		fprintf(sqlFile, "INSERT INTO cc_temp(course_id, number_of_credits) VALUES ('%s', %d);\n", courseID, credits);
		fprintf(sqlFile, "INSERT INTO cc_clone(course_id, number_of_credits) VALUES ('%s', %d);\n", courseID, credits);
	}

	fclose(fp);
	fclose(sqlFile);
	printf("%s\n", "Time Table data read successfully and SQL file generated.");

	return ;
}


/*
insert into cwsl(cid, serial_number, roll_number, name, email)
    values('temp', 1, 150101053, 'Roopansh Bansal', 'roopansh');
*/
void insert_cwsl(){
	FILE *sqlFile, *fp;
	struct dirent *MainDirectoryReader, *SubDirectoryReader;
	DIR *SubDirectory, *MainDirectory;
	char email[100], name[100], rollNo[20], BaseDir[100];
	int serialNo;

	printf("%s\n", "\nGenerating '150101053_cwsl.sql'");
	sqlFile = fopen("150101053_cwsl.sql", "w");
	if(sqlFile == NULL){
		printf("%s\n", "ERROR : Can't create '150101053_cwsl.sql'. Please Check");
		exit(1);
	}
	fprintf(sqlFile, "USE %s;\n", DATABASE_NAME);

	printf("%s\n", "Reading the Course Wise Students Database.");
	strcpy(BaseDir, "database-19-jan-2018/course-wise-students-list/" );

	MainDirectory = opendir(BaseDir);
	if (MainDirectory == NULL){
		printf("Could not open Base Directory." );
		exit(1);
	}

	while ((MainDirectoryReader = readdir(MainDirectory)) != NULL){
		// printf("%s\n", MainDirectoryReader->d_name);
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
			// printf("%s\n", SubDirectoryReader->d_name);
			if (strcmp(SubDirectoryReader->d_name, ".") == 0 || strcmp(SubDirectoryReader->d_name, "..") == 0 ){
				continue;
			}

			char temp2[200];
			strcpy(temp2, temp1);
			strcat(temp2, "/");
			strcat(temp2, SubDirectoryReader->d_name);
			// printf("%s\n", temp2);

			fp = fopen(temp2, "r");
			if(fp == NULL){
				printf("Error opening SOME file.\nEXIT.\n");
				exit(1);
			}

			char *course = strtok(SubDirectoryReader->d_name, ".");
			// printf("\tCOURSE:\t%s\n", course);
			while(fscanf(fp, "%d,%[^,],%[^,],%[^\n]\n", &serialNo, rollNo, name, email) != -1){
				// printf("%s\t%s\t%s\t%s\n",course, rollNo, name, email);
				fprintf(sqlFile, "INSERT INTO cwsl(cid, serial_number, roll_number, name, email) VALUES ('%s', %d, '%s', '%s', '%s');\n", course, serialNo, rollNo, name, email);
				fprintf(sqlFile, "INSERT INTO cwsl_temp(cid, serial_number, roll_number, name, email) VALUES ('%s', %d, '%s', '%s', '%s');\n", course, serialNo, rollNo, name, email);
				fprintf(sqlFile, "INSERT INTO cwsl_clone(cid, serial_number, roll_number, name, email) VALUES ('%s', %d, '%s', '%s', '%s');\n", course, serialNo, rollNo, name, email);
			}
			fclose(fp);

			while (course != NULL)
			{
				course = strtok(NULL, ".");
			}
		}
		closedir(SubDirectory);

	}
	closedir(MainDirectory);

	fclose(sqlFile);
	printf("%s\n", "Course-wise Students data read and SQL file generated successfully.");

	return ;
}
