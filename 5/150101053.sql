USE 09feb2018;

-- (a)
SELECT DISTINCT C.course_id AS 'COURSE ID'
    FROM Course AS C
    JOIN ScheduledIn AS S
    ON (C.course_id = S.course_id and C.division = S.course_division)
    WHERE S.room = '2001';

-- (b)
SELECT DISTINCT C.course_id AS 'COURSE ID'
    FROM Course AS C
    JOIN ScheduledIn AS S
    ON (C.course_id = S.course_id and C.division = S.course_division)
    WHERE S.slot_letter = 'C';

-- (c)
SELECT DISTINCT C.division AS 'DIVISION'
    FROM Course AS C
    JOIN ScheduledIn AS S
    ON (C.course_id = S.course_id and C.division = S.course_division)
    WHERE ( S.room = 'L1' or S.room = 'L2');

-- (d)
SELECT C.course_id AS 'COURSE ID'
    FROM Course AS C
    JOIN ScheduledIn AS S
    ON (C.course_id = S.course_id and C.division = S.course_division)
    GROUP BY C.course_id
    HAVING COUNT(DISTINCT S.room) > 1;

-- (e)
SELECT DISTINCT Dept.name AS 'DEPARTMENT NAME'
    FROM Department AS Dept
    JOIN ScheduledIn AS S
    ON (Dept.department_id = S.department)
    WHERE (S.room = 'L1' OR S.room = 'L2' OR S.room = 'L3' OR S.room = 'L4');

-- (f)
SELECT DISTINCT Dept.name AS 'DEPARTMENT NAME'
    FROM Department AS Dept
    JOIN ScheduledIn AS S
    ON (Dept.department_id = S.department)
    WHERE (S.room != 'L1' AND S.room != 'L2');

-- (g)
SELECT Dept.name AS 'DEPARTMENT NAME'
    FROM Department AS Dept
    JOIN ScheduledIn AS S
    ON (Dept.department_id = S.department)
    GROUP BY Dept.department_id
    HAVING COUNT(DISTINCT S.slot_letter) = (SELECT COUNT(DISTINCT slot.letter) FROM Slot AS slot);

-- (h)
SELECT S.slot_letter AS 'SLOT', COUNT(DISTINCT S.course_id) AS 'NUMBER OF COURSES'
    FROM ScheduledIn AS S
    GROUP BY S.slot_letter
    ORDER BY S.slot_letter ASC;

-- (i)
SELECT S.room AS 'ROOM NUMBER', COUNT(DISTINCT S.course_id) AS 'NUMBER OF COURSES'
    FROM ScheduledIn AS S
    GROUP BY S.room
    ORDER BY S.room DESC;

-- (j)
SELECT S.slot_letter AS 'SLOT NAME', COUNT(DISTINCT course_id) AS 'COUNT'
    FROM ScheduledIn AS S
    GROUP BY S.slot_letter
    ORDER BY COUNT asc
    LIMIT 1;

-- (k)
SELECT DISTINCT S.slot_letter AS 'SLOT'
    FROM ScheduledIn AS S
    WHERE S.course_id LIKE '%M';

-- (l) --- NOT WORKING
SELECT DISTINCT crossProduct.Dept AS 'Dept', crossProduct.Slot AS 'Slot'
    FROM (
          SELECT dept1.name AS 'Dept', slot1.letter AS 'Slot'
          from Slot AS slot1
          JOIN Department AS dept1
        ) AS crossProduct
     LEFT JOIN
        (
          SELECT dept2.name AS 'Dept', slot2.slot_letter AS 'Slot'
          FROM ScheduledIn AS slot2
          JOIN Department AS dept2
          ON dept2.department_id = slot2.department
        ) AS table1
    ON table1.Dept = crossProduct.Dept AND table1.slot = crossProduct.slot
    WHERE table1.dept IS NULL AND table1.slot IS NULL
    GROUP BY Dept
    ORDER BY Dept, Slot;

