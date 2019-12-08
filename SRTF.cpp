#include<stdio.h>
#include<limits.h>
#include<iostream>

struct process
{
  int p_id, arrival_time, burst_time, completion_time, waiting_time, turn_around_time, remaining_time;
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
    processes[i].remaining_time = processes[i].burst_time;
    processes[i].exec_complete = false;
  }
  std::cout<<std::endl;
   // +1 th element
  processes[no_of_processes].remaining_time = INT_MAX; // +1 th element, only for initial comparasion
  //printf("time => process number");
  auto count = 0;
  for (auto time = 0; count != no_of_processes; time++)
  {
    auto min_RT_index = no_of_processes;
    bubbleSort_p_id(processes, no_of_processes);
    for (auto i = 0; i < no_of_processes; i++)
    {
      if (processes[i].arrival_time <= time && 
          processes[i].remaining_time < processes[min_RT_index].remaining_time && 
          processes[i].remaining_time > 0 &&
          processes[i].exec_complete == false)
          {  
            min_RT_index = i;
            std::cout<<"| P"<<processes[min_RT_index].p_id<<"   |";
          }
    }
    processes[min_RT_index].remaining_time--;
    //printf("\n%d => p%d",time+1,min_RT_index);
    if(processes[min_RT_index].remaining_time == 0)
    {
      processes[min_RT_index].exec_complete = true;
      count++;
      end = time + 1;
      processes[min_RT_index].completion_time = end;
      processes[min_RT_index].waiting_time = end - processes[min_RT_index].arrival_time - processes[min_RT_index].burst_time;
      processes[min_RT_index].turn_around_time = end - processes[min_RT_index].arrival_time;
      std::cout<<"| P"<<processes[min_RT_index].p_id<<"   |";

    // printf("\n %d  %d   %d",min_RT_index,wt[min_RT_index],ttp[min_RT_index]);
    }
  }
  std::cout <<std::endl<< "Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time"<<std::endl;
  for (int i = 0; i < no_of_processes; i++)
  {
    std::cout << processes[i].p_id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].waiting_time << "\t\t" << processes[i].turn_around_time << "\n";
  }
  return 0;
}

// rutvik1999@Rutvik1999s-MacBook-Pro:~/OneDrive/OS_Lab/Sem 5 OS Lab$ cd "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/" && g++ -std=c++11 SRTF_cpy.cpp -o SRTF_cpy && "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/"SRTF_cpy

// Enter the number of Processes: 3

// Enter process ID of process: 1

// Enter arrival time of process with p_id = 1 : 2

// Enter burst time of process with p_id = 1 : 3

// Enter process ID of process: 2

// Enter arrival time of process with p_id = 2 : 3

// Enter burst time of process with p_id = 2 : 4

// Enter process ID of process: 3

// Enter arrival time of process with p_id = 3 : 2

// Enter burst time of process with p_id = 3 : 1

// | P1   || P3   || P3   || P1   || P1   || P1   || P1   || P2   || P2   || P2   || P2   || P2   |
// Process ID      Arrival Time    Burst Time      Completion Time Waiting Time    Turnaround Time
// 1               2               3               6               1               4
// 2               3               4               10              3               7
// 3               2               1               3               0               1