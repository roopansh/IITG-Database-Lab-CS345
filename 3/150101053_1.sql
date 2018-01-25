-- Creating Database ans using it
CREATE DATABASE 25jan2018;
USE 25jan2018;


-- Creating the main Tables --

-- none of the attributes of 'ett' can have NULL
CREATE TABLE ett (
    course_id CHAR(10) NOT NULL,
        -- courseID will be of type char(10) because it's of the form 'XY123[M]'
        -- Can't be PRIMARY_KEY beacuse there are multiple entries having the same courseID (Mid Sem and End Sem)
    exam_date DATE NOT NULL,
        -- Only store the DATE
    starttime TIME NOT NULL ,
        -- Only store the TIME
    endtime TIME NOT NULL ,
        -- Only store the TIME
    CONSTRAINT PK_ETT_COURSEID_EXAMDATE PRIMARY KEY(course_id, exam_date),
        -- Contsraint : one course can have only one exam on one date
    CONSTRAINT CHK_STARTTIME CHECK (starttime BETWEEN '09:00' AND '14:00'),
        -- starting time of exam is bwteen 9:00am and 2:00pm to avoid invalid exam timings
    CONSTRAINT CHK_ENDTIME CHECK (endtime BETWEEN '11:00' AND '17:00')
        --  ending time of exam is bwteen 11:00am and 5:00pm to avoid invalid exam timings
  );

-- none of the attributes of 'cc' can have NULL
CREATE TABLE cc (
  course_id CHAR(10),
        -- courseID will be of type char(10) because it's of the form 'XY123[M]'
  number_of_credits INT NOT NULL,
    -- Credits will be an INTEGER BETWEEN 1 and 9 always
  CONSTRAINT PK_CC_COURSEID PRIMARY KEY(course_id),
    -- Course ID will be PRIMARY_KEY (uniue and not Null) because each course will have only on entity in this table
    CONSTRAINT CHK_CREDITS CHECK (number_of_credits BETWEEN 1 AND 9)
    -- Credits will be an INTEGER BETWEEN 1 and 9 always
);

-- none of the attributes of 'cwsl' can have NULL
CREATE TABLE cwsl (
  cid CHAR(10) NOT NULL,
  serial_number int NOT NULL,
    -- Cannot be primary key because for every file of of every directory, serial numbers start from 1.
  roll_number CHAR(12),
    -- Generally Roll number is an integer of the form '150101053'. But since roll numbers like x170101053 also exist, Roll Number if a CHAR field
  name char(50) NOT NULL,
  email char(50) NOT NULL,
  CONSTRAINT PK_CWSL_ROLL_CID PRIMARY KEY(roll_number, cid)
    -- Contsraint : Each student should have a unique entry for each course he takes
);



-- Creating temporary Tables --
-- none of the attributes of 'ett' can have NULL
CREATE TEMPORARY TABLE ett_temp (
    course_id CHAR(10) NOT NULL,
        -- courseID will be of type char(10) because it's of the form 'XY123[M]'
        -- Can't be PRIMARY_KEY beacuse there are multiple entries having the same courseID (Mid Sem and End Sem)
    exam_date DATE NOT NULL,
        -- Only store the DATE
    starttime TIME NOT NULL ,
        -- Only store the TIME
    endtime TIME NOT NULL ,
        -- Only store the TIME
    CONSTRAINT PK_ETTTEMP_COURSEID_EXAMDATE PRIMARY KEY(course_id, exam_date),
        -- Contsraint : one course can have only one exam on one date
    CONSTRAINT CHK_STARTTIME_TEMP CHECK (starttime BETWEEN '09:00' AND '14:00'),
        -- starting time of exam is bwteen 9:00am and 2:00pm to avoid invalid exam timings
    CONSTRAINT CHK_ENDTIME_TEMP CHECK (endtime BETWEEN '11:00' AND '17:00')
        --  ending time of exam is bwteen 11:00am and 5:00pm to avoid invalid exam timings
  );

-- none of the attributes of 'cc' can have NULL
CREATE TEMPORARY TABLE cc_temp (
  course_id CHAR(10),
        -- courseID will be of type char(10) because it's of the form 'XY123[M]'
  number_of_credits INT NOT NULL,
    -- Credits will be an INTEGER BETWEEN 1 and 9 always
  CONSTRAINT PK_CCTEMP_COURSEID PRIMARY KEY(course_id),
    -- Course ID will be PRIMARY_KEY (uniue and not Null) because each course will have only on entity in this table
    CONSTRAINT CHK_CREDITS_TEMP CHECK (number_of_credits BETWEEN 1 AND 9)
    -- Credits will be an INTEGER BETWEEN 1 and 9 always
);

-- none of the attributes of 'cwsl' can have NULL
CREATE TEMPORARY TABLE cwsl_temp (
  cid CHAR(10) NOT NULL,
  serial_number int NOT NULL,
    -- Cannot be primary key because for every file of of every directory, serial numbers start from 1.
  roll_number CHAR(12),
    -- Generally Roll number is an integer of the form '150101053'. But since roll numbers like x170101053 also exist, Roll Number if a CHAR field
  name char(50) NOT NULL,
  email char(50) NOT NULL,
  CONSTRAINT PK_CWSLTEMP_ROLL_CID PRIMARY KEY(roll_number, cid)
    -- Contsraint : Each student should have a unique entry for each course he takes
);



-- Cloning the Tables --
CREATE TABLE ett_clone LIKE ett;
CREATE TABLE cc_clone LIKE cc;
CREATE TABLE cwsl_clone LIKE cwsl;
