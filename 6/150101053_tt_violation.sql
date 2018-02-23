USE 150101053_23feb2018;

DELETE FROM mysql.proc WHERE Db='150101053_23feb2018' AND TYPE ='PROCEDURE' AND NAME='tt_violation';

DELIMITER //

CREATE PROCEDURE tt_violation()
BEGIN

    -- Declare cur1 for cwsl
    -- Declare cur2 for cwsl
    -- fetch one record
    -- fetch it's time table
    -- fetch another record(ahead of the first record) having same roll number and diferent courseid
    -- fetch it's time table
    -- check clash and enter in a table
    DECLARE roll1 CHAR(10);
    DECLARE roll2 CHAR(10);
    DECLARE name CHAR(50);
    DECLARE course1 CHAR(5);
    DECLARE course2 CHAR(5);

    DECLARE date1 DATE;
    DECLARE date2 DATE;
    DECLARE start1 TIME;
    DECLARE start2 TIME;
    DECLARE end1 TIME;
    DECLARE end2 TIME;

    DECLARE cur1 CURSOR FOR (SELECT course_id, roll_number, name FROM cwsl);
    DECLARE cur2 CURSOR FOR (SELECT course_id, roll_number FROM cwsl WHERE roll_number=roll1);

    OPEN cur1;

    outer_loop: LOOP
        FETCH FROM cur1 INTO course1, roll1, name;

        OPEN cur2;

        inner_loop: LOOP

        END LOOP inner_loop;

        FETCH FROM cur2 INTO course2, roll2 ;
        select course1, roll1, name, course2, roll2;
        CLOSE cur2;

        LEAVE outer_loop;
    END LOOP outer_loop;
    CLOSE cur1;
END  //

DELIMITER ;
