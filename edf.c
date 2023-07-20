#include <stdio.h>
#include <stdlib.h>
#include "edf.h"
int period_copy[1000];//global array stores copy of period of tasks, used in hyperperiod calculation(lcm)
int get_tasks(task *t1)
{
	int i = 0;
	FILE* file;
	file=fopen("input.txt","r");
	if(file==NULL)//Error check 
	{
		printf("Error opening file.\n");
		exit(0);
	}

	while (!feof(file))//run till end of file is reached
	{
		if(ferror(file))
		{
			printf("Error opening file.\n");
			exit(0);
		}
		for(int j=0;j<4;j++)
		{
			if(fscanf(file,"%d",&t1->T[j])==EOF)
				break;
		}
		period_copy[i] = t1->T[period];//initialising period_copy
		t1->T[abs_arr] = 0;
		t1->T[temp_exec] = 0;
		t1->T[abs_dead] = 0;
		t1->T[last_exec]=0;
		t1->job = 0;
		t1->available = 0;
		t1++;
		i++;//calculates no. of tasks
	}
	fclose(file);
	return i;
}

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

int hyperperiod_calc(task *t1, int n)
{
	int i = 0, hp=1;
	for (i = 0; i < n; i++)//lcm logic 
	{
		//printf("res: %d period_copy[i]: %d gcd: %d\n",res,period_copy[i],gcd(res,period_copy[i]));
		hp = hp * period_copy[i] / gcd(hp, period_copy[i]);
	}
	return hp;
}

int update_availability(task *t1, int tmr, int n)
{
	int i = 0, n1 = 0, c= 0;
	while (i < n)
	{
		if (tmr == t1->T[abs_arr])
		{
			t1->available = 1;
			c++;
		}
		t1++;
		i++;
	}

	if ( c != 0)//Checking if atleast 1 job is available at that particular instant
	{
		return 1;
	}

	return 0;
}

void update_abs_dead(task *t1, int n, int flag)
{
	int i = 0;
	if (flag)
	{
		while (i < n)
		{
			t1->T[abs_dead] = t1->T[deadline] + t1->T[abs_arr];//absolute deadline = absolute arrival time + deadline
			t1++;
			i++;
		}
	}
	else
	{
		t1 += n;
		t1->T[abs_dead] = t1->T[deadline] + t1->T[abs_arr];
	}
}

void update_abs_arr(task *t1, int n, int k, int flag)
{
	int i = 0;
	if (flag)
	{
		while (i < n)
		{
			t1->T[abs_arr] = t1->T[arrival] + k * (t1->T[period]);//absolute arrival time = arrivaltime + job*period
			t1++;
			i++;
		}
	}
	else
	{
		t1 += n;
		t1->T[abs_arr] = t1->T[arrival] + k * (t1->T[period]);
	}
}

void copy_exec(task *t1, int n, int flag)
{
	int i = 0;
	if (flag)
	{
		while (i < n)
		{
			t1->T[temp_exec] = t1->T[execution];
			t1++;
			i++;
		}
	}
	else
	{
		t1 += n;
		t1->T[temp_exec] = t1->T[execution];
	}
}

int min_deadline(task *t1, int n)//returns task_id of task with minimum absolute deadline that is available
{
	int i = 0, min =1000, task_id = TASK_ID,last=-1;
	while (i < n)
	{
		if(t1->T[abs_dead]==min&&t1->available==1)
		{
			if(t1->T[last_exec]>last)
			{
				min = t1->T[abs_dead];
				task_id = i;
				last=t1->T[last_exec];
			}
		}
		else if (t1->T[abs_dead] < min && t1->available == 1)
		{
			min = t1->T[abs_dead];
			task_id = i;
			last=t1->T[last_exec];
		}
		t1++;
		i++;
	}
	return task_id;
}

double cpu_util(task *t1, int n)
{
	int i = 0;
	double cpu = 0.0;
	while (i < n)
	{
		cpu = cpu + (double)t1->T[execution] / (double)t1->T[deadline];
		t1++;
		i++;
	}
	return cpu;
}
