USE 09feb2018;

-- (a)
SELECT DISTINCT S.course_id AS 'COURSES IN ROOM 2001'
    FROM ScheduledIn AS S
    WHERE S.room = '2001';

-- (b)
SELECT DISTINCT S.course_id AS 'COURSES IN SLOT C'
    FROM ScheduledIn AS S
    WHERE S.slot_letter = 'C';

-- (c)
SELECT DISTINCT S.course_division AS 'DIVISION IN L2 OR L3'
    FROM ScheduledIn AS S
    WHERE ( S.room = 'L3' or S.room = 'L2');

-- (d)
SELECT S.course_id AS 'COURSES ALLOTED TO MULTIPLE ROOMS'
    FROM ScheduledIn AS S
    GROUP BY S.course_id
    HAVING COUNT(DISTINCT S.room) > 1;

-- (e)
SELECT DISTINCT Dept.name AS 'DEPARTMENTS ALLOTED L1 OR L2 OR L3 OR L4'
    FROM Department AS Dept
    JOIN ScheduledIn AS S
    ON (Dept.department_id = S.department)
    WHERE (S.room = 'L1' OR S.room = 'L2' OR S.room = 'L3' OR S.room = 'L4');

-- (f)
SELECT D1.name AS 'DEPARTMENT NOT USING L1 AND L2'
    FROM Department as D1
    WHERE D1.name NOT IN (
                          SELECT D2.name
                              FROM Department AS D2
                              JOIN ScheduledIn AS S
                              ON (D2.department_id = S.department)
                              WHERE (S.room = 'L1' OR S.room = 'L2')
                        );

-- (g)
SELECT Dept.name AS 'DEPARTMENT UTILISING ALL SLOTS'
    FROM Department AS Dept
    JOIN ScheduledIn AS S
    ON (Dept.department_id = S.department)
    GROUP BY Dept.department_id
    HAVING COUNT(DISTINCT S.slot_letter) = (SELECT COUNT(DISTINCT slot.letter) FROM Slot AS slot);

-- (h)
SELECT S.slot_letter AS 'SLOT', COUNT(DISTINCT S.course_id) AS 'NUMBER OF COURSES ASSIGNED'
    FROM ScheduledIn AS S
    GROUP BY S.slot_letter
    ORDER BY `NUMBER OF COURSES ASSIGNED` ASC;

-- (i)
SELECT S.room AS 'ROOM NUMBER', COUNT(DISTINCT S.course_id) AS 'NUMBER OF COURSES ASSIGNED'
    FROM ScheduledIn AS S
    GROUP BY S.room
    ORDER BY `NUMBER OF COURSES ASSIGNED` DESC;

-- (j)
SELECT `SLOT NAME ASSIGNED MIN COURSES`
    FROM(
         SELECT S.slot_letter AS 'SLOT NAME ASSIGNED MIN COURSES', COUNT(*) AS 'COUNT'
         FROM ScheduledIn AS S
         GROUP BY S.slot_letter
         ORDER BY COUNT ASC
         LIMIT 1
        ) AS Table1;

-- (k)
SELECT DISTINCT S.slot_letter AS 'SLOTS ASSIGNED MINORS'
    FROM ScheduledIn AS S
    WHERE S.course_id LIKE '%M';

-- (l)
SELECT crossProduct.Dept AS 'DEPARTMENT NAME', crossProduct.Slot AS 'SLOT UNUSED'
    FROM (
          SELECT DISTINCT dept1.name AS 'Dept', slot1.letter AS 'Slot'
          from Slot AS slot1
          JOIN Department AS dept1
        ) AS crossProduct
     LEFT JOIN
        (
          SELECT DISTINCT dept2.name AS 'Dept', slot2.slot_letter AS 'Slot'
          FROM ScheduledIn AS slot2
          JOIN Department AS dept2
          ON dept2.department_id = slot2.department
        ) AS table1
    ON table1.Dept = crossProduct.Dept AND table1.slot = crossProduct.slot
    WHERE table1.dept IS NULL AND table1.slot IS NULL
    ORDER BY `DEPARTMENT NAME`, `SLOT UNUSED`;

