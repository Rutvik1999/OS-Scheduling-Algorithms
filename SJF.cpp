#include<iostream> 

using namespace std;

    struct process
{
    int p_id, arrival_time, burst_time, completion_time, waiting_time, turn_around_time;
};

void swap(struct process *a, struct process *b) 
{ 
    struct process prev_process_completion_time = *a; 
    *a = *b; 
    *b = prev_process_completion_time; 
} 

void bubbleSort_arrival_time(struct process processes[], int n)  
{    
    for (int i = 0; i < n - 1; i++)      
        for (int j = 0; j < n - i - 1; j++)  
            if (processes[j].arrival_time > processes[j+1].arrival_time)  
                swap(&processes[j], &processes[j+1]);  
}

void completionTime(struct process processes[], int no_of_processes)
{
    int prev_process_completion_time, val;
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turn_around_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turn_around_time - processes[0].burst_time;

    for (int i = 1; i < no_of_processes; i++)
    {
        prev_process_completion_time = processes[i - 1].completion_time;
        int current_process_burst_time = processes[i].burst_time;
        for (int j = i; j < no_of_processes; j++)  
        {
            if (prev_process_completion_time >= processes[j].arrival_time && processes[j].burst_time <= current_process_burst_time)
            {
                current_process_burst_time = processes[j].burst_time;
                val = j;
            }
        }
        processes[val].completion_time = prev_process_completion_time + processes[val].burst_time;
        processes[val].turn_around_time = processes[val].completion_time - processes[val].arrival_time;
        processes[val].waiting_time = processes[val].turn_around_time - processes[val].burst_time;
        swap(processes[val], processes[i]);
    }
}
  
int main() 
{ 
    int no_of_processes, prev_process_completion_time; 
    
    cout<<"Enter no_of_processes: "; 
    cin>>no_of_processes;
    struct process processes[no_of_processes]; 
      
    cout<<"...Enter the process ID...\n For : \n"; 
    for(int i = 0; i < no_of_processes; i++) 
    { 
        cout<<"Process "<<i+1<<"\n"; 
        cout<<"Enter Process Id: "; 
        cin>>processes[i].p_id; 
        cout<<"Enter Arrival Time: "; 
        cin>>processes[i].arrival_time; 
        cout<<"Enter Burst Time: "; 
        cin>>processes[i].burst_time; 
    } 
      
    cout<<"Before Arrange...\n"; 
    cout<<"Process ID\tArrival Time\tBurst Time\n"; 
    for(int i = 0; i < no_of_processes; i++) 
    { 
        cout<<processes[i].p_id<<"\t\t"<<processes[i].arrival_time<<"\t\t"<<processes[i].burst_time<<"\n"; 
    } 
    bubbleSort_arrival_time(processes, no_of_processes);
    completionTime(processes, no_of_processes);
    cout<<"Final Result...\n"; 
    cout<<"Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n"; 
    for(int i = 0; i < no_of_processes; i++) 
    { 
        cout<<processes[i].p_id<<"\t\t"<<processes[i].arrival_time<<"\t\t"<<processes[i].burst_time<<"\t\t"<<processes[i].completion_time<<"\t\t"<<processes[i].waiting_time<<"\t\t"<<processes[i].turn_around_time<<"\n"; 
    } 
} 

// rutvik1999@Rutvik1999s-MacBook-Pro:~/OneDrive/OS_Lab/Sem 5 OS Lab$ cd "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/" && g++ -std=c++11 SJF.cpp -o SJF && "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/"SJF
// Enter no_of_processes: 4
// ...Enter the process ID...
//  For : 
// Process 1
// Enter Process Id: 1
// Enter Arrival Time: 0
// Enter Burst Time: 3
// Process 2
// Enter Process Id: 2
// Enter Arrival Time: 1
// Enter Burst Time: 2
// Process 3
// Enter Process Id: 3
// Enter Arrival Time: 1
// Enter Burst Time: 4
// Process 4
// Enter Process Id: 4
// Enter Arrival Time: 5
// Enter Burst Time: 5
// Before Arrange...
// Process ID      Arrival Time    Burst Time
// 1               0               3
// 2               1               2
// 3               1               4
// 4               5               5
// Final Result...
// Process ID      Arrival Time    Burst Time      Completion Time Waiting Time    Turnaround Time
// 1               0               3               3               0               3
// 2               1               2               5               2               4
// 3               1               4               9               4               8
// 4               5               5               14              4               9