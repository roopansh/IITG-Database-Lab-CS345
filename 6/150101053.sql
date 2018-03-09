DROP DATABASE 150101053_23feb2018;

CREATE DATABASE 150101053_23feb2018;

USE 150101053_23feb2018;

CREATE TABLE cc(
                course_id CHAR(8),
                number_of_credits INT,
                CONSTRAINT PK_CC_COURSEID PRIMARY KEY(course_id)
);

CREATE TABLE ett (
                  line_number INT,
                  course_id CHAR(8),
                  exam_date DATE,
                  start_time TIME,
                  end_time TIME,
                  CONSTRAINT PK_ETT_COURSEID_EXAMDATE PRIMARY KEY(course_id, exam_date),
                  CONSTRAINT FK_ETT_CC_COURSE_ID FOREIGN KEY(course_id) REFERENCES cc(course_id)
);

CREATE TABLE cwsl(
                  serial_number INT,
                  roll_number CHAR(10),
                  name CHAR(50),
                  email CHAR(100),
                  course_id CHAR(8),
                  CONSTRAINT PK_CWSL_ROLL_CID PRIMARY KEY(roll_number, course_id),
                  CONSTRAINT FK_CWSL_CC_COURSE_ID FOREIGN KEY(course_id) REFERENCES cc(course_id)
);
