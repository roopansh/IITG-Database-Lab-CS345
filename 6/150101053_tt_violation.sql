USE 150101053_23feb2018;

DELETE FROM mysql.proc WHERE Db='150101053_23feb2018' AND TYPE ='PROCEDURE' AND NAME='tt_violation';

DELIMITER //

-- Displays students who have a exam time table clash
CREATE PROCEDURE tt_violation()
BEGIN
    -- Variables declaration
    DECLARE roll_number CHAR(10);
    DECLARE name CHAR(50);
    DECLARE course1 CHAR(8);
    DECLARE course2 CHAR(8);
    DECLARE exam_date DATE;
    DECLARE start_time1 TIME;
    DECLARE start_time2 TIME;
    DECLARE end_time1 TIME;
    DECLARE end_time2 TIME;
    DECLARE done BOOLEAN DEFAULT FALSE;

    -- Cursor 1 Declaration - for looping through all the entries of CWSL JOIN ETT
    DECLARE cur1 CURSOR FOR
        SELECT cwsl.roll_number, cwsl.name, ett.exam_date, ett.start_time, ett.end_time, cwsl.course_id FROM (cwsl JOIN ett on cwsl.course_id = ett.course_id );

    -- Cursor 2 Declaration - for fetching all the exam dates of the current student selected by cursor 1 and on the same date as that of the selected course of the first student
    DECLARE cur2 CURSOR FOR
        SELECT ett.start_time, ett.end_time, cwsl.course_id FROM (cwsl JOIN ett on cwsl.course_id = ett.course_id) WHERE cwsl.roll_number = roll_number AND ett.exam_date = exam_date AND cwsl.course_id < course1;

    -- Continue Handler
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

    -- Create a temporary table to enter the required records into it and then displaying them altogether at the end
    CREATE TEMPORARY TABLE tt_violation_temp(roll_number CHAR(10),
                                                            name CHAR(50),
                                                            course1 char(8),
                                                            course2 char(8)
                                                            );

    -- Open cursor-1 and start the outer loop
    OPEN cur1;
    outer_loop: LOOP

        -- Fetch from cursor 1
        FETCH FROM cur1 INTO roll_number, name, exam_date, start_time1, end_time1, course1;

        -- If no more data to fetch, then the continue handler is called and sets `done` = TRUE
        -- When finishing, close the open cursor-1 and leave the outerloop
        IF done = TRUE THEN
            CLOSE cur1;
            LEAVE outer_loop;
        END IF;

        OPEN cur2;
        inner_loop: LOOP

            -- Fetch from cursor 2
            FETCH FROM cur2 INTO start_time2, end_time2, course2;

            -- If no more data to fetch, then the continue handler is called and sets `done` = TRUE
            -- When finishing, close the open cursor-2 and leave the leave loop
            -- Set `DONE` to FALSE to prevent it from leaving the outerloop as well
            IF done = TRUE THEN
                SET done = FALSE;
                CLOSE cur2;
                LEAVE inner_loop;
            END IF;

            -- If there is a time clash, then add the entry to the temporary table
            IF (start_time2 <= start_time1 AND end_time2 >= start_time1) OR (start_time1 <= start_time2 AND end_time1 >= start_time2) THEN
                INSERT INTO tt_violation_temp VALUES(roll_number, name, course1, course2);
            END IF;
        END LOOP inner_loop;
    END LOOP outer_loop;

    -- display the added entries of the temporary table
    SELECT DISTINCT * FROM tt_violation_temp;
    DROP TABLE tt_violation_temp;

END  //

DELIMITER ;
