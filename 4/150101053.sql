-- DATABASE CREATION

CREATE DATABASE 09feb2018;
USE 09feb2018;

-- COURSES TABLES
CREATE TABLE Course(
                    course_id CHAR(10) NOT NULL,
                  -- COURSE ID Cannot be NULL, No default Value
                    division ENUM('I', 'II', 'III', 'IV', 'NA') NOT NULL DEFAULT 'NA',
                  -- Domain is contrained by using ENUM, and it's default value is 'NA' and Cannot be NULL.
                    CONSTRAINT PK_COURSE_COURSEIDDIVISION PRIMARY KEY (course_id, division)
                  -- key is chosen as the CourseID, Division Pair itself because one course can be divided into many divisions
);

-- DEPARTMENTS TABLES
CREATE TABLE Department(
                        department_id CHAR(10) NOT NULL,
                      -- Department id cannot be NULL and has no default value
                        name CHAR(50) NOT NULL,
                      -- Department name cannot be NULL and has no default value
                        CONSTRAINT PK_DEPARTMENT_DEPTARTMENTID PRIMARY KEY (department_id)
                      -- Department id is the primary key
);

-- SLOTS TABLES
CREATE TABLE Slot(
                  letter ENUM('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'A1', 'B1', 'C1', 'D1', 'E1') NOT NULL,
                -- domain is constrained using enum, and it cannot be null. No default value
                  day ENUM('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday') NOT NULL,
                -- domain is constrained using enum, and it cannot be null. No default value
                  start_time TIME NOT NULL,
                  end_time TIME NOT NULL,
                  CONSTRAINT PK_SLOT_LETTERDAY PRIMARY KEY (letter, day),
                -- Primary key is letter-day pair
                  CONSTRAINT CHECK_SLOT_TIME CHECK (start_time < end_time)
                -- need to check that the start time of the exam is less than end time
);

-- ROOMS TABLES
CREATE TABLE Room(
                  room_number CHAR(20) NOT NULL,
                -- Room number cannot be null
                  location ENUM('Core-I', 'Core-II', 'Core-III', 'Core-IV', 'LH', 'Local') NOT NULL,
                -- location's domain is constrained
                  CONSTRAINT PK_ROOM_ROOMNUMBER PRIMARY KEY (room_number)
                -- room number alone suffices as the primary key
);


-- SCHEDULED IN RELATION
CREATE TABLE ScheduledIn(
                        -- All the primary keys of the other tables:-
                         course_id CHAR(10) NOT NULL,
                         course_division ENUM('I', 'II', 'III', 'IV', 'NA') NOT NULL DEFAULT 'NA',
                         department CHAR(10) NOT NULL,
                         slot_letter ENUM('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'A1', 'B1', 'C1', 'D1', 'E1') NOT NULL,
                         slot_day ENUM('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday') NOT NULL,
                         room CHAR(20) NOT NULL,

                         -- Foreign keys to different tables, not that on deleting or updating the enteries in main table, entries of this table are also deleted or updated accordingly,
                         CONSTRAINT FK_SCHEDULEDIN_COURSE FOREIGN KEY (course_id, course_division) REFERENCES Course(course_id, division) ON DELETE CASCADE ON UPDATE CASCADE,
                         CONSTRAINT FK_SCHEDULEDIN_DEPARTMENT FOREIGN KEY (department) REFERENCES Department(department_id) ON DELETE CASCADE ON UPDATE CASCADE,
                         CONSTRAINT FK_SCHEDULEDIN_SLOT FOREIGN KEY (slot_letter, slot_day) REFERENCES Slot(letter, day) ON DELETE CASCADE ON UPDATE CASCADE,
                         CONSTRAINT FK_SCHEDULEDIN_ROOM FOREIGN KEY (room) REFERENCES Room(room_number) ON DELETE CASCADE ON UPDATE CASCADE,

                         -- PRIMARY KEY CONSTRAINTS

                         CONSTRAINT PK_SCHEDULEDIN PRIMARY KEY (course_id, slot_letter, slot_day, room)

                         -- CONSTRAINT PK_SCHEDULEDIN_1 PRIMARY KEY(slot_letter, slot_day, room)
                         -- we can't keep slot_letter, slot_day, room as key because two different courses are being taught together - CH438, CH643

                         -- CONSTRAINT PK_SCHEDULEDIN_2 PRIMARY KEY(course_id, course_division, slot_letter, slot_day)
                         -- we can't keep course_id, course_division, slot_letter, slot_day as key because same courses is being held in different rooms at the same time - E.g. - Mechanical Engineering Second and Third Year Courses

                         -- keeping all the attributes as pk is not useful

);


-- Populate Data

-- LOAD EVERY CSV FILE

LOAD DATA LOCAL INFILE "csv/150101053_department.csv"
INTO TABLE Department
COLUMNS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE "csv/150101053_slot.csv"
INTO TABLE Slot
COLUMNS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE "csv/150101053_room.csv"
INTO TABLE Room
COLUMNS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE "csv/150101053_course.csv"
INTO TABLE Course
COLUMNS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE "csv/150101053_scheduledin.csv"
INTO TABLE ScheduledIn
COLUMNS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;
