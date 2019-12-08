#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

struct process
{
    int p_id, arrival_time, burst_time, completion_time, waiting_time, turn_around_time, remaining_time;
    bool exec_complete;
};

int Queue[100];
auto front = -1, rear=0;

void insertBack(int p)
{
    if(rear == 100)
    {
        cout<<"Queue is full!!\n";
        exit(0);
    }
    Queue[rear++] = p;
    if(front == -1) 
    {
        ++front;
    }
}

void exec_process_RR(struct process processes[], int no_of_processes, int time_quantum, int first_arrived_process_index)
{
    memset(Queue, -1, sizeof(Queue));
    int totalBT = 0;
    for(auto i = 0; i < no_of_processes; i++)
    {
        totalBT = totalBT + processes[i].burst_time;
    }

    insertBack(first_arrived_process_index);
    int last_process_exec__time = processes[first_arrived_process_index].arrival_time;
    while(totalBT)
    {
        if(Queue[front] == -1)
        {
            int MIN = INT_MAX, index;
            for(int i = 0; i < no_of_processes; i++)
            {
                if (processes[i].arrival_time > last_process_exec__time)
                {
                    if (processes[i].arrival_time < MIN)
                    {
                        MIN = processes[i].arrival_time;
                        index = i;
                    }
                }
            }
            last_process_exec__time = MIN;
            insertBack(index);
        }
        //cout<<"Front : "<<Queue[front]<<"\n";

        int process_min_RT = std::min(time_quantum, processes[Queue[front]].remaining_time);
        processes[Queue[front]].completion_time = (last_process_exec__time + process_min_RT);
        processes[Queue[front]].remaining_time -= process_min_RT;
        processes[Queue[front]].turn_around_time = processes[Queue[front]].completion_time - processes[Queue[front]].arrival_time;
        processes[Queue[front]].waiting_time = processes[Queue[front]].turn_around_time - processes[Queue[front]].burst_time;
        totalBT -= process_min_RT;

        for(int i = last_process_exec__time + 1; i<= last_process_exec__time + process_min_RT; i++)
        {
            for(int j=0; j < no_of_processes; j++)
            {
                if(processes[j].arrival_time == i)
                {
                    insertBack(j);
                }
            }
        }

        if(processes[Queue[front]].remaining_time != 0)
        {
            insertBack(Queue[front]);
        }
        
        ++front;
        last_process_exec__time += process_min_RT;
    }
    cout << "\nQueue : \n";
    for (int i = 0; i < rear; i++)
    {
        cout << Queue[i] << " ";
    }
    cout << "\n";
}

int main()
{
    int no_of_processes;
    cout << "Enter no_of_processes : ";
    cin >> no_of_processes;
    struct process processes[no_of_processes];
    int time_quantum;
    auto first_process_AT = INT_MAX;
    int first_arrived_process_index;
    cout << "Enter time_quantum :";
    cin >> time_quantum;
    cout << "...Enter the process ID...\n";
    for (int i = 0; i < no_of_processes; i++)
    {
        cout << "Process " << i + 1 << "\n";
        cout << "Enter Process Id: ";
        cin >> processes[i].p_id;
        cout << "Enter Arrival Time: ";
        cin >> processes[i].arrival_time;
        cout << "Enter Burst Time: ";
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].exec_complete = false;
        processes[i].completion_time = 0;
        if(processes[i].arrival_time < first_process_AT)
        {
           first_process_AT = processes[i].arrival_time;
           first_arrived_process_index = i;
        }

    }

    cout << "Before Arrange...\n";
    cout << "Process ID\tArrival Time\tBurst Time\n";
    for (int i = 0; i < no_of_processes; i++)
    {
        cout << processes[i].p_id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\n";
    }
    cout << endl;
    exec_process_RR(processes, no_of_processes, time_quantum, first_arrived_process_index);

    cout << "Final Result...\n";
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < no_of_processes; i++)
    {
        cout << processes[i].p_id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].waiting_time << "\t\t" << processes[i].turn_around_time << "\n";
    }
}

// rutvik1999@Rutvik1999s-MacBook-Pro:~$ cd "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/" && g++ -std=c++11 RoundRobin.cpp -o RoundRobin && "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/"RoundRobin
// Enter no_of_processes : 3
// Enter time_quantum :2
// ...Enter the process ID...
// Process 1
// Enter Process Id: 1
// Enter Arrival Time: 0
// Enter Burst Time: 3
// Process 2
// Enter Process Id: 2
// Enter Arrival Time: 2
// Enter Burst Time: 4
// Process 3
// Enter Process Id: 3
// Enter Arrival Time: 3
// Enter Burst Time: 6
// Before Arrange...
// Process ID      Arrival Time    Burst Time
// 1               0               3
// 2               2               4
// 3               3               6


// Queue : 
// 0 1 0 2 1 2 2 
// Final Result...
// Process ID      Arrival Time    Burst Time      Completion Time Waiting Time    Turnaround Time
// 1               0               3               5               2               5
// 2               2               4               9               3               7
// 3               3               6               13              4               10