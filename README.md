# EDF-scheduling-algorithm
Implemented the EDF (Earliest Deadline First) scheduling algorithm in C as a part of the operating systems curriculum. Developed a custom scheduler that prioritized tasks based on their deadlines, ensuring timely execution and meeting critical task requirements. Input has been taken using file.
/* Assumption:-
If 2 jobs have different absolute deadlines, the one with earliest deadline will be executed first.
If the absolute deadlines of 2 jobs is same the one which is cache hot or alreadly been executed will 
be executed first
If both have have same deadline and neither has been executed job with lower task_id is executed.*/

/*To compile use command: gcc main.c edf.c
						  ./a.out             */
