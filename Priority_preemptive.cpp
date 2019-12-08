#include<stdio.h>
#include<limits.h>
#include<iostream>

struct process
{
  int p_id, arrival_time, burst_time, completion_time, waiting_time, turn_around_time, remaining_time, priority;
  bool exec_complete;
};

void swap(struct process *a, struct process *b)
{
  struct process temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort_p_id(struct process processes[], int n)
{
  for (int i = 0; i < n - 1; i++)

    // Last i elements are already in place
    for (int j = 0; j < n - i - 1; j++)
      if (processes[j].p_id > processes[j + 1].p_id)
        swap(&processes[j], &processes[j + 1]);
}

void bubbleSort_priority(struct process processes[], int n)
{
  for (int i = 0; i < n - 1; i++)

    // Last i elements are already in place
    for (int j = 0; j < n - i - 1; j++)
      if (processes[j].priority > processes[j + 1].priority)
        swap(&processes[j], &processes[j + 1]);
}

int main()
{
  auto no_of_processes = 0, end = 0;
  printf("\nEnter the number of Processes: ");
  scanf("%d",&no_of_processes);
  struct process processes[no_of_processes + 1];
  for(auto i = 0; i < no_of_processes; i++)
  {
    printf("\nEnter process ID of process: ");
    scanf("%d", &processes[i].p_id);
    printf("\nEnter arrival time of process with p_id = %d : ", processes[i].p_id);
    scanf("%d",&processes[i].arrival_time);
    printf("\nEnter burst time of process with p_id = %d : ", processes[i].p_id);
    scanf("%d", &processes[i].burst_time);
    printf("\nEnter priority of process with p_id = %d : ", processes[i].p_id);
    scanf("%d", &processes[i].priority);
    processes[i].remaining_time = processes[i].burst_time;
    processes[i].exec_complete = false;
  }
   // +1 th element
  processes[no_of_processes].priority = INT_MIN; // +1 th element, only for initial comparasion
  //printf("time => process number");
  auto count = 0;
  for (auto time = 0; count != no_of_processes; time++)
  {
    auto max_priority_index = no_of_processes;
    bubbleSort_p_id(processes, no_of_processes);
    bubbleSort_priority(processes, no_of_processes);
    for (auto i = 0; i < no_of_processes; i++)
    {
      if (processes[i].arrival_time <= time && 
          processes[i].priority > processes[max_priority_index].priority && 
          processes[i].remaining_time > 0 &&
          processes[i].exec_complete == false)
            {
              max_priority_index = i;
            }
    }
    processes[max_priority_index].remaining_time--;
    //printf("\n%d => p%d",time+1,max_priority_index);
    if(processes[max_priority_index].remaining_time == 0)
    {
      processes[max_priority_index].exec_complete = true;
      count++;
      end = time + 1;
      processes[max_priority_index].completion_time = end;
      processes[max_priority_index].turn_around_time = processes[max_priority_index].completion_time - processes[max_priority_index].arrival_time;
      processes[max_priority_index].waiting_time = processes[max_priority_index].turn_around_time - processes[max_priority_index].burst_time;
      // printf("\n %d  %d   %d",max_priority_index,wt[max_priority_index],ttp[max_priority_index]);
    }
  }
  std::cout << "Process ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time"<<std::endl;
  for (int i = 0; i < no_of_processes; i++)
  {
    std::cout << processes[i].p_id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].priority<<"\t\t"<< processes[i].completion_time << "\t\t" << processes[i].waiting_time << "\t\t" << processes[i].turn_around_time << "\n";
  }
  return 0;
}

// rutvik1999@Rutvik1999s-MacBook-Pro:~/OneDrive/OS_Lab/Sem 5 OS Lab$ cd "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/" && g++ -std=c++11 Priority_preemptive.cpp -o Priority_preemptive && "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/"Priority_preemptive

// Enter the number of Processes: 3

// Enter process ID of process: 1

// Enter arrival time of process with p_id = 1 : 0

// Enter burst time of process with p_id = 1 : 3

// Enter priority of process with p_id = 1 : 2

// Enter process ID of process: 2

// Enter arrival time of process with p_id = 2 : 1

// Enter burst time of process with p_id = 2 : 5

// Enter priority of process with p_id = 2 : 3

// Enter process ID of process: 3

// Enter arrival time of process with p_id = 3 : 3

// Enter burst time of process with p_id = 3 : 1

// Enter priority of process with p_id = 3 : 7
// Process ID      Arrival Time    Burst Time      Priority        Completion Time Waiting Time    Turnaround Time
// 1               0               3               2               9               6               9
// 2               1               5               3               7               1               6
// 3               3               1               7               4               0               1