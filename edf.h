#define arrival 0	//0 index denotes arrival time
#define deadline 1	//1 index denotes deadline of task
#define period 2	//2 index denotes period of task
#define execution 3	//3 index denotes execution time of task
#define abs_arr 4	//4 index denotes absolute arrival time of a job
#define temp_exec 5	//5 index stores a copy of execution time which will be decreemented as it is executed
#define abs_dead 6	//6 index denotes the absolute deadline of a job
#define last_exec 7	//7 index denotes the last time when a particular job was executed
typedef struct
{
	int T[8];
	int job,available;
/*
		T is an array with indexing from 0-7 containing details of each task

		job : denotes Number of times the tasks had arrived since time = 0)
		available : denotes if the task is available currently? 0 for unavailable and 1 for available
*/
}task;

#define TASK_ID 1248   // Just a number I assigned which will be updated with task_id of task in execution

int get_tasks(task *t1);				//takes input from input.txt file
void copy_exec(task *t1,int n,int flag);	//makes a copy of execution time
void update_abs_arr(task *t1,int n,int k,int flag);	//updates absolute arrival time 
void update_abs_dead(task *t1,int n,int flag);	//updates absolute deadline 
double cpu_util(task *t1,int n);				//calculates CPU utilization using (Execution/Deadline) formula
int gcd(int a, int b);					//returns greatest common divisor of a and b
int hyperperiod_calc(task *t1,int n);			//calculates hyperiod period of the tasks given 
int update_availability(task *t1,int tmr,int n);	//at each instant updates availability state of each task
int min_deadline(task *t1,int n);		//Find minimum absolute deadline task



