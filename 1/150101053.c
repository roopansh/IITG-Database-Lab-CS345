#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

// Student Data Structure 
typedef struct Student{
	int RollNo;

	// Storing the Date  attendance is held. (Dynamically Grows as more and more Data is read)	
	char **HeldOn;
	char *Attendance;
	int Total, MaxSize;

	int Present;
	int Absent;
} Student;

Student *students;					

// Function Prototypes
int ReadCSV();
void GenerateResult(int );
void PrintStoredStudents();

// Main Function
int main(){
	int studentSize = ReadCSV();
	GenerateResult(studentSize);

	// PrintStoredStudents();  /* FOR DEBUGGING */
	return 0;
}

int ReadCSV(){
	int curStudSize = 0, maxStudSize = 9;
	students = (Student *) calloc(10, sizeof(Student));

	FILE *fp;
	int roll, flag, i;
	char date[20], attendance[20];

	printf("Reading the Original Database.\n");
	// Read the CSV file, Search among students for the roll no. and increase the corresponding attendance(Absent/Fail)
	fp = fopen("database_12jan2017.csv", "r");

	if(fp == NULL){
		printf("Error opening 'database_12jan2017.csv' file.\nEXIT.\n");
		exit(1);
	}

	while(fscanf(fp, "%d , %s %s\n", &roll, date, attendance) != -1){	// Read CSV file till the end of the file
		// printf("%d %s %s\n", roll, date, attendance);
		flag = 1;
		for(i = 0; i < curStudSize; i++){
			if (students[i].RollNo == roll){	// if student already present in the students
				flag = 0;

				strcpy(students[i].HeldOn[students[i].Total-1], date);
				// Increase 'Present' or 'Absent' of the student accordingly
				if(strcmp(attendance,"Present") == 0){
					students[i].Present++;
					students[i].Attendance[students[i].Total-1] = 'P';
				} else if (strcmp(attendance,"Absent") == 0){
					students[i].Absent++;
					students[i].Attendance[students[i].Total-1] = 'A';
				}
				students[i].Total++;

				if(students[i].Total == students[i].MaxSize){
					students[i].HeldOn = realloc(students[i].HeldOn, (students[i].MaxSize+10)*sizeof(char*));
					int x;
					for(x = students[i].Total; x < students[i].Total + 10; x++){
						students[i].HeldOn[x] = (char*)calloc(20, sizeof(char));
					}
					students[i].Attendance = realloc(students[i].Attendance, (students[i].MaxSize+10)*sizeof(char));
					students[i].MaxSize += 10;
				}

				break;
			}
		}

		// If student is not present in the students, Add it
		if(flag == 1){
			students[curStudSize].RollNo = roll;
			
			// Increase 'Present' or 'Absent' of the student accordingly
			if(strcmp(attendance,"Present") == 0){
				students[i].Present = 1;
				students[i].Absent = 0;
				students[i].Total = 1;
				students[i].HeldOn = (char**)calloc(10, sizeof(char*));
				int x;
				for(x = 0; x < 10; x++){
					students[i].HeldOn[x] = (char*)calloc(20, sizeof(char));
				}
				strcpy(students[i].HeldOn[students[i].Total-1], date);
				students[i].Attendance = (char *)calloc(10, sizeof(char));
				students[i].Attendance[students[i].Total-1] = 'P';
			} else if (strcmp(attendance,"Absent") == 0){
				students[i].Absent = 1;
				students[i].Present = 0;
				students[i].Total = 1;
				students[i].HeldOn = (char**)calloc(10, sizeof(char*));
				int x;
				for(x = 0; x < 10; x++){
					students[i].HeldOn[x] = (char*)calloc(20, sizeof(char));
				}
				strcpy(students[i].HeldOn[students[i].Total-1], date);
				students[i].Attendance = (char *)calloc(10, sizeof(char));
				students[i].Attendance[students[i].Total-1] = 'A';
			}
			students[i].Total++;
			students[i].MaxSize = 10;
			curStudSize++;

			if(curStudSize == maxStudSize){
				// Dynamically allocate more memory to the students
				students = realloc(students, (maxStudSize+10)*sizeof(Student));
				maxStudSize += 10;
			}
		}
	}	
	// Close the orginal Database CSV File
	fclose(fp);
	return curStudSize;
}


void GenerateResult(int studSize){
	FILE *G75, *L75;
	int i, roll;
	float present, absent, maxAttendance, finalAttendance;

	// Calcluate the Attendance and Print to the Required file accordingly
	printf("Generating the required 'G75.CSV' and 'L75.CSV' files.\n");
	G75 = fopen("G75.csv", "w");
	L75 = fopen("L75.csv", "w");

	if(G75 == NULL){
		printf("Error creating 'G75.csv' file.\nEXIT.\n");
		exit(1);
	}

	if(L75 == NULL){
		printf("Error creating 'L75.csv' file.\nEXIT.\n");
		exit(1);
	}

	for(i=0; i<studSize; i++){
		// printf("%d\t%d\t%d\n", students[i].RollNo, students[i].Present, students[i].Absent);
		roll = students[i].RollNo;
		present = students[i].Present;
		absent = students[i].Absent;
		maxAttendance = present + absent;
		finalAttendance = (present*100)/maxAttendance;
		
		if(finalAttendance >= 75.0){
			fprintf(G75, "%d , %f ,  %.2f % \n", roll, present, finalAttendance);
		} else {
			fprintf(L75, "%d , %f ,  %.2f % \n", roll, present, finalAttendance);
		}
	}

	// Close the G75 and L75 csv files.
	fclose(G75);
	fclose(L75);
	printf("Files Generated successfully.\n");
}

/* FOR DEBUGGING PURPOSE */
void PrintStoredStudents(){
	Student s = students[0];
	int i ;
	for(i = 0; i < s.Total; i++){
		printf("%s\t%c\n", s.HeldOn[i], s.Attendance);
	}
}