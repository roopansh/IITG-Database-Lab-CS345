USE 150101053_23feb2018;

DELETE FROM mysql.proc WHERE Db='150101053_23feb2018' AND TYPE ='PROCEDURE' AND NAME='count_credits';

DELIMITER //

CREATE PROCEDURE count_credits()
BEGIN
    -- Variables declaration
    DECLARE roll_number CHAR(10);
    DECLARE name CHAR(50);
    DECLARE total_credits INT;
    DECLARE credits INT;
    DECLARE done BOOLEAN DEFAULT FALSE;

    -- Cursor 1 Declaration - for looping through all the entries of CWSL and getting distinct students
    DECLARE cur1 CURSOR FOR SELECT DISTINCT cwsl.roll_number FROM cwsl;

    -- Cursor 2 Declaration - for looping through all the courses and credits of the student selected through cursor-1
    DECLARE cur2 CURSOR FOR SELECT cc.number_of_credits, cwsl.name FROM cwsl JOIN cc ON cwsl.course_id = cc.course_id WHERE cwsl.roll_number = roll_number;

    -- Continue Handler
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

    -- Create a temporary table to enter the required records into it and then displaying them altogether at the end
    CREATE TEMPORARY TABLE count_credits_temp (roll_number CHAR(10),
                                                name CHAR(50),
                                                credits INT);

    -- Open cursor-1 and start the outer loop
    OPEN cur1;
    outer_loop: LOOP

        -- Fetch from cursor 1
        FETCH FROM cur1 INTO roll_number;

        -- If no more data to fetch, then the continue handler is called and sets `done` = TRUE
        -- When finishing, close the open cursor-1 and leave the outerloop
        IF done = TRUE THEN
            CLOSE cur1;
            LEAVE outer_loop;
        END IF;

        -- Reset the value of total_credits for each student initially
        SET total_credits = 0;

        OPEN cur2;
        inner_loop: LOOP

      		-- Fetch from cursor 2
            FETCH FROM cur2 INTO credits, name;

            -- If no more data to fetch, then the continue handler is called and sets `done` = TRUE
            -- When finishing, close the open cursor-2 and leave the leave loop
            -- Set `DONE` to FALSE to prevent it from leaving the outerloop as well
            IF done = TRUE THEN
                SET done = FALSE;
                CLOSE cur2;
                LEAVE inner_loop;
            END IF;

            -- Add the credits of the current course fetched by the cursor 2
            SET total_credits = total_credits + credits;
        END LOOP inner_loop;

        -- If total_credits exceed 40, then add to the temporary table
        IF total_credits > 40 THEN
        	INSERT INTO count_credits_temp(roll_number, name, credits) VALUES (roll_number, name, total_credits);
        END IF;

    END LOOP outer_loop;

    -- display the added entries of the temporary table
    SELECT * FROM count_credits_temp ORDER BY count_credits_temp.credits, count_credits_temp.roll_number;
    DROP TABLE count_credits_temp;

END //

DELIMITER ;
