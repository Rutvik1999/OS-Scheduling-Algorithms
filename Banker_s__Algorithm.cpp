#include <iostream>
#include <stdio.h>

bool all_exec(bool arr[], int size)
{
    bool temp = true;
    for(int i = 0; i < size; i++)
    {
        temp = temp && arr[i];
    }
    return temp;
}

bool does_satisfy_resources_condition(int current_arr[], int requirement_arr[], int no_of_resources)
{
    for(int i = 0; i < no_of_resources; i++)
    {
        if((current_arr[i] - requirement_arr[i]) < 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int no_of_processes = 0, no_of_resources = 0;
    std::cout << "Enter number of Processes: "<<std::endl;
    std::cin >> no_of_processes;
    std::cout << "Enter number of Resources: "<<std::endl;
    std::cin >> no_of_resources;
    int allocated_matrix[no_of_processes][no_of_resources];
    for(int i = 0; i < no_of_processes; i++)
    {
        std::cout<<"Enter Allocated Resources value for process "<<i<<std::endl;
        for(int j = 0; j < no_of_resources; j++)
        {
            scanf("%d", &allocated_matrix[i][j]);
        }
    }
    int max_matrix[no_of_processes][no_of_resources];
    for(int i = 0; i < no_of_processes; i++)
    {
        std::cout<<"Enter Max Required Resources value for process "<<i<<std::endl;
        for(int j = 0; j < no_of_resources; j++)
        {
            scanf("%d", &max_matrix[i][j]);
        }
    }

    int max_available_resources_vector[no_of_resources];
    for(int i = 0; i < no_of_resources; i++)
    {
        std::cout<<std::endl<<"Maximum Available Value for Resource "<<i<<" :";
        std::cin>>max_available_resources_vector[i];
    }

    int requirement_matrix[no_of_processes][no_of_resources];
    std::cout << "\nRequired Resources Matrix" << std::endl<< "-----------------------" << std::endl;
    for(int i = 0; i < no_of_processes; i++)
    {
        for(int j = 0; j < no_of_resources; j++)
        {
            requirement_matrix[i][j] = max_matrix[i][j] - allocated_matrix[i][j];
            std::cout<<requirement_matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"-----------------------"<<std::endl;
    std::cout << "\nAllocated Resources Matrix" << std::endl<< "-----------------------" << std::endl;
    for (int i = 0; i < no_of_processes; i++)
    {
        for (int j = 0; j < no_of_resources; j++)
        {
            std::cout << allocated_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
    bool successful_exec_vector_arr[no_of_processes];
    for(int i  = 0; i < no_of_processes; i++)
    {
        successful_exec_vector_arr[i] = false;
    }

    int current_available_resources[no_of_resources];
    for(int i = 0; i < no_of_resources; i++)
    {
        current_available_resources[i] = 0;
    }

    for (int i = 0; i < no_of_resources; i++)
    {
        for (int j = 0; j < no_of_processes; j++)
        {
            current_available_resources[i] += allocated_matrix[j][i];
        }
    }
    std::cout<<"\nCurrent Available resources vector\n";
    for(int i = 0; i < no_of_resources; i++)
    {
        current_available_resources[i] = max_available_resources_vector[i] - current_available_resources[i];
        std::cout<<current_available_resources[i]<<" ";
    }
    std::cout<<std::endl;
    int safe_seq[no_of_processes];
    int deadlock__indicator = 0; //deadlock if > 5000
    bool successful_exec_completed = false;
    int seq_count = 0;
    while((!all_exec(successful_exec_vector_arr, no_of_processes)) && deadlock__indicator < 5000)
    {
        deadlock__indicator++;
        start_processes:
        for(int i = 0; i < no_of_processes; i++)
        {
            //std::cout << does_satisfy_resources_condition(current_available_resources, requirement_matrix[i], no_of_resources)<<std::endl;
            if ((successful_exec_vector_arr[i] == false) && does_satisfy_resources_condition(current_available_resources, requirement_matrix[i], no_of_resources))
            {
                std::cout<<"Available resource vector after executing process "<<i<<std::endl;
                for(int j = 0; j < no_of_resources; j++)
                {
                    current_available_resources[j] = current_available_resources[j] + allocated_matrix[i][j];
                    std::cout<<current_available_resources[j]<<" ";
                }
                std::cout<<std::endl;
                successful_exec_vector_arr[i] = true;
                safe_seq[seq_count++] = i;
                goto start_processes;
            }
        }
    }
    successful_exec_completed = all_exec(successful_exec_vector_arr, no_of_processes);
    if(successful_exec_completed == true)
    {
        std::cout<<std::endl<<"Safe Sequence : ";
        for(int i = 0; i < no_of_processes; i++)
        {
            std::cout<<"P"<<safe_seq[i]<<" -> ";
        }
        std::cout<<"END"<<std::endl;
    }
    if(successful_exec_completed == false)
    {
        std::cout<<std::endl<<"---------Deadlock Encoutered---------"<<std::endl;
    }
}

// rutvik1999@Rutvik1999s-MacBook-Pro:~/OneDrive/OS_Lab/Sem 5 OS Lab$ cd "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/" && g++ -std=c++11 Banker_s__Algorithm.cpp -o Banker_s__Algorithm && "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/"Banker_s__Algorithm
// Enter number of Processes: 
// 4
// Enter number of Resources: 
// 3
// Enter Allocated Resources value for process 0
// 0 1 0
// Enter Allocated Resources value for process 1
// 2 0 0
// Enter Allocated Resources value for process 2
// 3 0 2
// Enter Allocated Resources value for process 3
// 2 1 1
// Enter Max Required Resources value for process 0
// 7 5 3
// Enter Max Required Resources value for process 1
// 3 2 2
// Enter Max Required Resources value for process 2
// 9 0 2
// Enter Max Required Resources value for process 3
// 2 2 2

// Maximum Available Value for Resource 0 :10

// Maximum Available Value for Resource 1 :5

// Maximum Available Value for Resource 2 :7

// Required Resources Matrix
// -----------------------
// 7 4 3 
// 1 2 2 
// 6 0 0 
// 0 1 1 
// -----------------------

// Allocated Resources Matrix
// -----------------------
// 0 1 0 
// 2 0 0 
// 3 0 2 
// 2 1 1 
// -----------------------

// Current Available resources vector
// 3 3 4 
// Available resource vector after executing process 1
// 5 3 4 
// Available resource vector after executing process 3
// 7 4 5 
// Available resource vector after executing process 0
// 7 5 5 
// Available resource vector after executing process 2
// 10 5 7 

// Safe Sequence : P1 -> P3 -> P0 -> P2 -> END