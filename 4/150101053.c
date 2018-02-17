#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char DATABASE_NAME[] = "09feb2018";

void populateCourses();
void populateDepartment();
void populateSlot();
void populateRoom();
void populateSchedulein();

/* The main function */
int main(int argc, char const *argv[])
{
	populateCourses();
	populateDepartment();
	populateSlot();
	populateRoom();
	populateSchedulein();
	return 0;
}


/*
* Populate the 'course' table of the database.
*/
void populateCourses(){
	FILE *sqlFile, *fp;
	char courseID[10], division[5];

	sqlFile = fopen("150101053_course.sql", "w");
	if(sqlFile == NULL){
		fprintf(stderr, "%s\n", "ERROR : Can't create '150101053_courses.sql'.");
		exit(1);
	}

	fp = fopen("150101053_course.csv", "r");
	if(fp == NULL){
		fprintf(stderr, "Error opening '150101053_course.csv' file.\n");
		fclose(sqlFile);
		exit(1);
	}

	fprintf(sqlFile, "USE %s;\n\n", DATABASE_NAME);

	while(fscanf(fp, "%[^,], %[^\n]\n", courseID, division) != -1){
		fprintf(sqlFile, "INSERT INTO Course(course_id, division) VALUES('%s', '%s');\n", courseID, division);
	}

	fclose(fp);
	fclose(sqlFile);
	fprintf(stderr, "%s\n\n", "Courses data read successfully and SQL file generated.");

	return ;
}


/*
* Populate the Departments table of the database.
*/
void populateDepartment(){
	FILE *sqlFile, *fp;
	char deptID[10], name[50];

	sqlFile = fopen("150101053_department.sql", "w");
	if(sqlFile == NULL){
		fprintf(stderr, "%s\n", "ERROR : Can't create '150101053_department.sql'.");
		exit(1);
	}

	fp = fopen("150101053_department.csv", "r");
	if(fp == NULL){
		fprintf(stderr, "Error opening '150101053_department.csv' file.\n");
		fclose(sqlFile);
		exit(1);
	}

	fprintf(sqlFile, "USE %s;\n\n", DATABASE_NAME);

	while(fscanf(fp, "%[^,], %[^\n]\n", deptID, name) != -1){
		fprintf(sqlFile, "INSERT INTO Department(department_id, name) VALUES('%s', '%s');\n", deptID, name);
	}

	fclose(fp);
	fclose(sqlFile);
	fprintf(stderr, "%s\n\n", "Departments data read successfully and SQL file generated.");

	return ;
}


/*
* Populate the Slots table of the database.
*/
void populateSlot(){
	FILE *sqlFile, *fp;
	char letter[3], day[20], starttime[10], endtime[10];

	sqlFile = fopen("150101053_slot.sql", "w");
	if(sqlFile == NULL){
		fprintf(stderr, "%s\n", "ERROR : Can't create '150101053_slot.sql'.");
		exit(1);
	}

	fp = fopen("150101053_slot.csv", "r");
	if(fp == NULL){
		fprintf(stderr, "Error opening '150101053_slot.csv' file.\n");
		fclose(sqlFile);
		exit(1);
	}

	fprintf(sqlFile, "USE %s;\n\n", DATABASE_NAME);

	while(fscanf(fp, "%[^,], %[^,], %[^,], %[^\n]\n", letter, day, starttime, endtime) != -1){
		fprintf(sqlFile, "INSERT INTO Slot(letter, day, start_time, end_time) VALUES('%s', '%s', '%s', '%s');\n", letter, day, starttime, endtime);
	}

	fclose(fp);
	fclose(sqlFile);
	fprintf(stderr, "%s\n\n", "Slots data read successfully and SQL file generated.");

	return ;
}

/*
* Populate the Room table of the database.
*/
void populateRoom(){
	FILE *sqlFile, *fp;
	char room_number[10], location[10];

	sqlFile = fopen("150101053_room.sql", "w");
	if(sqlFile == NULL){
		fprintf(stderr, "%s\n", "ERROR : Can't create '150101053_room.sql'.");
		exit(1);
	}

	fp = fopen("150101053_room.csv", "r");
	if(fp == NULL){
		fprintf(stderr, "Error opening '150101053_room.csv' file.\n");
		fclose(sqlFile);
		exit(1);
	}

	fprintf(sqlFile, "USE %s;\n\n", DATABASE_NAME);

	while(fscanf(fp, "%[^,], %[^\n]\n", room_number, location) != -1){
		fprintf(sqlFile, "INSERT INTO Room(room_number, location) VALUES('%s', '%s');\n", room_number, location);
	}

	fclose(fp);
	fclose(sqlFile);
	fprintf(stderr, "%s\n\n", "Room data read successfully and SQL file generated.");

	return ;
}


/*
* Populate the Schedules In table of the database.
*/
void populateSchedulein(){
	FILE *sqlFile, *fp;

	char course_id[10], course_division[5], department[5], slot_letter[5], slot_day[20], room[10];

	sqlFile = fopen("150101053_scheduledin.sql", "w");
	if(sqlFile == NULL){
		fprintf(stderr, "%s\n", "ERROR : Can't create '150101053_scheduledin.sql'.");
		exit(1);
	}

	fp = fopen("150101053_scheduledin.csv", "r");
	if(fp == NULL){
		fprintf(stderr, "Error opening '150101053_scheduledin.csv' file.\n");
		fclose(sqlFile);
		exit(1);
	}

	fprintf(sqlFile, "USE %s;\n\n", DATABASE_NAME);

	while(fscanf(fp, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", course_id, course_division, department, slot_letter, slot_day, room) != -1){
		fprintf(sqlFile, "INSERT INTO ScheduledIn(course_id, course_division, department, slot_letter, slot_day, room) VALUES('%s', '%s', '%s', '%s', '%s', '%s');\n", course_id, course_division, department, slot_letter, slot_day, room);
	}

	fclose(fp);
	fclose(sqlFile);
	fprintf(stderr, "%s\n\n", "Scheduled In data read successfully and SQL file generated.");

	return ;
}