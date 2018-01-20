#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

typedef struct CourseCredit{
	char courseID[10];
	int Credits;
} CourseCredit;

typedef struct Student{
	char Name[100], Email[100], RollNo[20];
	int totalCredits;
} Student;

typedef struct TimeTable{
	char courseID[10], date[20], startTime[10], endTime[10];
} TimeTable;

typedef struct CourseStudent{
	char courseID[10];
	char RollNo[20];
} CourseStudent;


int main(){
	FILE *fp;
	char courseID[10], date[20], startTime[10], endTime[10], email[100], name[100], rollNo[20];
	int serialNo, credits, count, i, CourseCount, TimeTableCount;
	
	CourseStudent *courseStudent;
	courseStudent = (CourseStudent *) calloc(100, sizeof(CourseStudent));
	int curCourseSudSize = 0, MaxCourseStudSize = 99;

	Student *students;
	int curStudSize = 0, maxStudSize = 99;
	students = (Student *) calloc(100, sizeof(Student));


	printf("\n\n%s\n\n", "Put the CODE in 'database-19-jan-2018' directory with the Question PDF File. ");

	printf("%s\n", "Reading the Course Credits.");
	// Course Credits
	fp = fopen("database-19-jan-2018/course-credits.csv", "r");
	if(fp == NULL){
		printf("Error opening 'database-19-jan-2018/course-credits.csv' file.\nEXIT.\n");
		exit(1);
	}

	count = 0;
	while(fscanf(fp, "%[^,],%d\n", courseID, &credits) != -1){
		// printf("%s %d\n", courseID, credits);
		count++;
	}
	// printf("%d", count );
	CourseCount = count;
	CourseCredit *courseCredit;
	courseCredit = (CourseCredit *) calloc(count+5, sizeof(CourseCredit));
	
	i = 0;
	fseek(fp, 0, SEEK_SET);
	while(fscanf(fp, "%[^,],%d\n", courseID, &credits) != -1){
		// printf("%s %d\n", courseID, credits);
		strcpy(courseCredit[i].courseID, courseID);
		courseCredit[i].Credits = credits;
		i++;
	}

	fclose(fp);
	printf("%s\n", "Course Credits data read successfully.");


	printf("\n\n%s\n", "Reading the Time Table.");
	// TimeTable
	fp = fopen("database-19-jan-2018/exam-time-table.csv", "r");
	if(fp == NULL){
		printf("Error opening 'database-19-jan-2018/exam-time-table.csv' file.\nEXIT.\n");
		exit(1);
	}

	count = 0;
	while(fscanf(fp, "%[^,], %[^,], %[^,], %[^\n]\n", courseID, date, startTime, endTime) != -1){
		// printf("%s %s %s %s\n", courseID, date, startTime, endTime);
		count++;
	}

	// printf("%d", count );
	TimeTableCount = count;
	TimeTable *timeTable;
	timeTable = (TimeTable *) calloc(count+5, sizeof(TimeTable));
	
	i = 0;
	fseek(fp, 0, SEEK_SET);
	while(fscanf(fp, "%[^,], %[^,], %[^,], %[^\n]\n", courseID, date, startTime, endTime) != -1){
		// printf("%s %s %s %s\n", courseID, date, startTime, endTime);
		strcpy(timeTable[i].courseID, courseID);
		strcpy(timeTable[i].date, date);
		strcpy(timeTable[i].startTime, startTime);
		strcpy(timeTable[i].endTime, endTime);
		i++;
	}

	fclose(fp);
	printf("%s\n", "Time Table data read successfully");

	printf("\n\n%s\n", "Reading the Course Wise Students Database.");
	char BaseDir[100];
	strcpy(BaseDir, "database-19-jan-2018/course-wise-students-list/" );


	struct dirent *MainDirectoryReader, *SubDirectoryReader;
	DIR *SubDirectory, *MainDirectory;

	MainDirectory = opendir(BaseDir);
	if (MainDirectory == NULL){
		printf("Could not open Base Directory." );
		return 0;
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
			return 0;
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

				// add student course student
				strcpy(courseStudent[curCourseSudSize].courseID, course);
				strcpy(courseStudent[curCourseSudSize].RollNo, rollNo);
				curCourseSudSize++;

				// add student
				int x = 0, flag = 1;
				for(x = 0; x < curStudSize; x++){
					if(strcmp(students[x].RollNo, rollNo) == 0){
						flag = 0;
						break;
					}
				}
				if(flag == 1){
					strcpy(students[curStudSize].RollNo, rollNo);
					strcpy(students[curStudSize].Email, email);
					strcpy(students[curStudSize].Name, name);
					students[curStudSize].totalCredits = 0;
					curStudSize++;
				}

				// search and add student
				if(curCourseSudSize == MaxCourseStudSize){
					// Dynamically allocate more memory to the coursestudents
					courseStudent = realloc(courseStudent, (MaxCourseStudSize+100)*sizeof(CourseStudent));
					MaxCourseStudSize += 100;
				}

				if(curStudSize == maxStudSize){
					// Dynamically allocate more memory to the students
					students = realloc(students, (maxStudSize+100)*sizeof(Student));
					maxStudSize += 100;
				}
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
    

	/***************************
			DEBUG PURPOSE
	PRINT ALL THE DATA COLLECTED
	****************************/
	/*
	// Print all the students
	int x = 0;
	
	for(x = 0; x < curStudSize; x++){
		// printf("%s\n", students[x].RollNo);
	}

	// Print all the CoursesStudents
	for(x = 0; x < curCourseSudSize; x++){
		// printf("%s\t%s\n", courseStudent[x].RollNo, courseStudent[x].courseID);
	}

	// Print all the courses and Credits
	for(x = 0; x < CourseCount; x++){
		// printf("%s\t%d\n", courseCredit[x].courseID, courseCredit[x].Credits);
	}	

	// Print the time Table
	for(x = 0; x < TimeTableCount; x++){
		// printf("%s\t%s\t%s\t%s\n", timeTable[x].courseID,timeTable[x].date, timeTable[x].startTime, timeTable[x].endTime);
	}
	*/


	/***************************
			CONSTRAINT - 2
			TOTAL CREDITS
	****************************/
	printf("\n\n%s\n", "CONSTRAINT_2.");
	printf("\t%s\n", "Calculating the total credits of each student");
	// calculate total credits of each student
	int x = 0;
	for(x = 0; x < curStudSize; x++){								// for every student
		int y = 0;
		for(y = 0; y < curCourseSudSize; y++){						// find every course taken by him
			if(strcmp(students[x].RollNo, courseStudent[y].RollNo) == 0){
				int z = 0;
				for(z = 0; z < CourseCount; z++){					// add the course's credits
					if (strcmp(courseCredit[z].courseID, courseStudent[y].courseID) == 0){
						students[x].totalCredits += courseCredit[z].Credits;
						break;
					}
				}	
			}
		}
	}	

	fp = fopen("CONSTRAINT_2.csv", "w");
	// Print all the students with credits greater than 40
	if (fp == NULL){
		printf("\t%s\n", "Error opening the 'CONSTRAINT_2.csv' file.");
		return 0;
	}

	for(x = 0; x < curStudSize; x++){
		if(students[x].totalCredits	> 40){
			fprintf(fp, "%s,%s,%d\n", students[x].RollNo,students[x].Name, students[x].totalCredits);
			// printf("%d,%s,%s\n",x, students[x].RollNo,students[x].Name);
		}
	}
	printf("\t%s\n", "'CONSTRAINT_2.csv generated successfully.");
	

	/***************************
			CONSTRAINT - 1
		EXAM TIME TABLE CLASH
	****************************/

	printf("\n\n%s\n", "CONSTRAINT_1.");
	printf("\t%s\n", "Processing the Clashes in the Time Table.");

	fp = fopen("CONSTRAINT_1.csv", "w+");
	if (fp == NULL){
		printf("\t%s\n", "Error opening the 'CONSTRAINT_1.csv' file.");
		return 0;
	}
	for(x = 0; x < curStudSize; x++){								// for every student
		int y1, y2;
		for(y1 = 0; y1 < curCourseSudSize; y1++){						// find every pair of course taken by him
			if(strcmp(students[x].RollNo, courseStudent[y1].RollNo) == 0){					// COURSE 1
				for(y2 = y1+1; y2 < curCourseSudSize; y2++){
					if(strcmp(students[x].RollNo, courseStudent[y2].RollNo) == 0){			// COURSE 2
						// Compare the dates and time of these pairs
						int z1, z2;
						for(z1 = 0; z1 < TimeTableCount; z1++){
							if (strcmp(courseStudent[y1].courseID, timeTable[z1].courseID) == 0){
								for(z2 = 0; z2 < TimeTableCount; z2++){
									if (strcmp(courseStudent[y2].courseID, timeTable[z2].courseID) == 0){
										if (strcmp(timeTable[z1].date, timeTable[z2].date) == 0){
											if (strcmp(timeTable[z1].startTime, timeTable[z2].startTime) == 0){
												if (strcmp(timeTable[z1].endTime, timeTable[z2].endTime) == 0){
													
													// read the csv and check for duplicates
													fseek(fp, 0, SEEK_SET);
													char rollNo[20], name[100], c1[10], c2[10];
													int flag = 1;
													while(fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", rollNo, name, c1, c2) != -1){
														if ( (strcmp(rollNo ,students[x].RollNo) == 0) && (strcmp(c1,courseStudent[y1].courseID) == 0) && (strcmp(c2,courseStudent[y2].courseID) == 0) ){
															// printf("%s\t%s\t%s\t%s\n", rollNo, name, c1, c2);
															// printf("%d\t%d\t%d\t%d\t%d\t\n", x, y1, y2, z1, z2);
															flag = 0;
															break;
														}
													}
													if(flag == 1){
														fprintf(fp, "%s,%s,%s,%s\n", students[x].RollNo, students[x].Name, courseStudent[y1].courseID, courseStudent[y2].courseID);	
													}
													else {
														continue;
													}
												}
											}
										}										
									}
								}
							}
						}
					}
				}
			}
		}
	}	
	fclose(fp);
	printf("\t%s\n", "'CONSTRAINT_1.csv generated successfully.");

	printf("%s\n", "EXIT");

    return 0;
}