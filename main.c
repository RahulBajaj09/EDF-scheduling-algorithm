
/* Assumption:-
If 2 jobs have different absolute deadlines, the one with earliest deadline will be executed first.
If the absolute deadlines of 2 jobs is same the one which is cache hot or alreadly been executed will 
be executed first
If both have have same deadline and neither has been executed job with lower task_id is executed.*/

/*To compile use command: gcc main.c edf.c
						  ./a.out             */

#include <stdio.h>
#include <stdlib.h>
#include "edf.h"

//Time that will count till hyperperiod
int time = 0;

int main()
{
	task *t;
	int n=8, hyper_period, task_id=TASK_ID;
	double cpu;
	t = malloc(n * sizeof(task));
	n=get_tasks(t);
	cpu= cpu_util(t, n);
	printf("CPU Utilization %f\n", cpu);

	hyper_period = hyperperiod_calc(t, n);
	printf("Hyper Period: %d\n",hyper_period);

	if (cpu<= 1.000000)
		printf("Tasks can be scheduled as :\n");
	else
	{
		printf("Schedule is not possible for given input\n");
		exit(0);
	}

	//initializing all variables of task
	copy_exec(t, n, 1);
	update_abs_arr(t, n, 0, 1);
	update_abs_dead(t, n, 1);

	while (time < hyper_period)
	{

		if (update_availability(t, time, n))//if at least one task is alive find task with minimum deadline
		{
			task_id = min_deadline(t, n);
		}
		if (task_id == TASK_ID)//if task_id is not updated idle state
		{
			printf("%d - %d Idle\n", time,time+1);
		}
		if (task_id != TASK_ID)
		{

			if (t[task_id].T[temp_exec] != 0)
			{
				t[task_id].T[temp_exec]--;//reduce execution unit by 1
				t[task_id].T[last_exec]=time;
				printf("%d - %d Task %d Job %d\n", time,time+1, task_id + 1,t[task_id].job+1);
			}

			if (t[task_id].T[temp_exec] == 0)//execution complete
			{
				t[task_id].job++;
				t[task_id].available = 0;
				//reinitialize all variables of task
				copy_exec(t, task_id, 0);
				update_abs_arr(t, task_id, t[task_id].job, 0);
				update_abs_dead(t, task_id, 0);
				task_id = min_deadline(t, n);
			}
		}
		++time;
	}
	free(t);
	return 0;
}
