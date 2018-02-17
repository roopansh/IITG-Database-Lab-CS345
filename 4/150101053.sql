CREATE DATABASE 09feb2018;

USE 09feb2018;

CREATE TABLE Course(
                    course_id CHAR(10) NOT NULL,
                    division ENUM('I', 'II', 'III', 'IV', 'NA') DEFAULT 'NA',
                    CONSTRAINT PK_COURSE_COURSEIDDIVISION PRIMARY KEY (course_id, division)
);

CREATE TABLE Department(
                        department_id CHAR(10) NOT NULL,
                        name CHAR(50) NOT NULL,
                        CONSTRAINT PK_DEPARTMENT_DEPTARTMENTID PRIMARY KEY (department_id)
);

CREATE TABLE Slot(
                  letter ENUM('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'A1', 'B1', 'C1', 'D1', 'E1') NOT NULL,
                  day ENUM('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday') NOT NULL,
                  start_time TIME NOT NULL,
                  end_time TIME NOT NULL,
                  CONSTRAINT PK_SLOT_LETTERDAY PRIMARY KEY (letter, day),
                  CONSTRAINT CHECK_SLOT_TIME CHECK (start_time < end_time)
);

CREATE TABLE Room(
                  room_number CHAR(20) NOT NULL,
                  location ENUM('Core-I', 'Core-II', 'Core-III', 'Core-IV', 'LH', 'Local') NOT NULL,
                  CONSTRAINT PK_ROOM_ROOMNUMBER PRIMARY KEY (room_number)
);

CREATE TABLE ScheduledIn(
                         course_id CHAR(10) NOT NULL,
                         course_division ENUM('I', 'II', 'III', 'IV', 'NA') NOT NULL,
                         department CHAR(10) NOT NULL,
                         slot_letter ENUM('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'A1', 'B1', 'C1', 'D1', 'E1') NOT NULL,
                         slot_day ENUM('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'),
                         room CHAR(20) NOT NULL,
                         CONSTRAINT FK_SCHEDULEDIN_COURSE FOREIGN KEY (course_id, course_division) REFERENCES Course(course_id, division) ON DELETE CASCADE,
                         CONSTRAINT FK_SCHEDULEDIN_DEPARTMENT FOREIGN KEY (department) REFERENCES Department(department_id) ON DELETE CASCADE,
                         CONSTRAINT FK_SCHEDULEDIN_SLOT FOREIGN KEY (slot_letter, slot_day) REFERENCES Slot(letter, day) ON DELETE CASCADE,
                         CONSTRAINT FK_SCHEDULEDIN_ROOM FOREIGN KEY (room) REFERENCES Room(room_number) ON DELETE CASCADE
);
