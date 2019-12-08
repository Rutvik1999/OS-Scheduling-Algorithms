#include <stdio.h>
#include <stdlib.h>

struct process_info
{
    int p_no;
    int burst_time;
    int arrival_time;
    int turn_around_time;
    int wait_time;
    int completion_time;
};

int sort(struct process_info arr[], int n);

    int main()
{
    int n_process, temp = 0;
    float AvTAT = 0, AvWT = 0;
    printf ("Enter the number of processes : ");
    scanf ("%d", &n_process);
    struct process_info arr[n_process];

    for (int i = 0; i < n_process; i++)
    {
        arr[i].p_no = i;
        printf ("\nEnter data for Process-%d : \n", arr[i].p_no + 1 );
        printf ("Enter Arrival Time : ");
        scanf ("%d", &(arr[i].arrival_time));
	    printf ("Enter Burst Time   : ");
        scanf ("%d", &(arr[i].burst_time));
    }
    //Sorting the processes according to their arrival time
    sort(arr, n_process);
    printf ("SCHEDULE\nProcess\t\tArrival Time\t Burst Time\t Completion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < n_process; i++)
    {
        if(i > 0)
        {
            if(arr[i].arrival_time > arr[i-1].completion_time)
                arr[i].completion_time = arr[i].arrival_time + arr[i].burst_time;
            else 
                arr[i].completion_time = arr[i-1].completion_time + arr[i].burst_time;
        }
        if(i == 0)
        {
            arr[i].completion_time = arr[i].arrival_time + arr[i].burst_time + 1;
        }
	    arr[i].turn_around_time = (arr[i].completion_time - 1)- arr[i].arrival_time;
        arr[i].wait_time = arr[i].turn_around_time - arr[i].burst_time;
        AvTAT = AvTAT + arr[i].turn_around_time;
        AvWT = AvWT + arr[i].wait_time;
        printf ("%4d\t%14d\t\t%5d\t%16d\t%17d\t%15d\n", 
                arr[i].p_no + 1, arr[i].arrival_time, arr[i].burst_time, arr[i].completion_time - 1, arr[i].turn_around_time, arr[i].wait_time);
    } // -1 because. we count from 0
    printf("\n");
    printf("Average Turn Around Time: %f\nAverage Waiting Time: %f\n", AvTAT / n_process, AvWT / n_process);
    return 0;
}

//Bubble Sort
int sort(struct process_info arr[], int n)
{
    int i, j;
    struct process_info temp_k = arr[0];

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            //Sorting the processes according to their arrival time
            if (arr[i].arrival_time > arr[j].arrival_time)
            {
                temp_k = arr[i];
                arr[i] = arr[j];
                arr[j] = temp_k;
            }
        }
    }
    return 0;
}

// rutvik1999@Rutvik1999s-MacBook-Pro:~$ cd "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/" && gcc FCFS.c -o FCFS && "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/"FCFS
// Enter the number of processes : 5

// Enter data for Process-1 : 
// Enter Arrival Time : 0
// Enter Burst Time   : 3

// Enter data for Process-2 : 
// Enter Arrival Time : 1
// Enter Burst Time   : 6

// Enter data for Process-3 : 
// Enter Arrival Time : 3
// Enter Burst Time   : 7

// Enter data for Process-4 : 
// Enter Arrival Time : 5
// Enter Burst Time   : 5

// Enter data for Process-5 : 
// Enter Arrival Time : 8
// Enter Burst Time   : 8
// SCHEDULE
// Process         Arrival Time     Burst Time      Completion Time        Turn Around Time        Waiting Time
//    1                 0              3                  3                        3                     0
//    2                 1              6                  9                        8                     2
//    3                 3              7                 16                       13                     6
//    4                 5              5                 21                       16                    11
//    5                 8              8                 29                       21                    13

// Average Turn Around Time: 12.200000
// Average Waiting Time: 6.400000