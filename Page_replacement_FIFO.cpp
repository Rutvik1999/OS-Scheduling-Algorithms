#include <iostream>
#include <stdio.h>

struct mem_req_info
{
    int p_id, in_time;
};

bool is_current_process_in_cache(struct mem_req_info arr[], int size, struct mem_req_info mem_req_p_id_current)
{
    for(int i = 0; i < size; i++)
    {
        if(arr[i].p_id == mem_req_p_id_current.p_id)
        {
            return true;
        }
        else continue;
    }
    return false;
}

bool all_used(struct mem_req_info arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(arr[i].p_id == -1)
            return false; 
    }
    return true;
}

int main()
{
    int f_size, p_ref_len;
    int page_fault = 0;
    std::cout<<"Enter Frame Size : ";
    std::cin>>f_size;
    std::cout<<"Enter Page refrence (Sequence) Length : ";
    std::cin>>p_ref_len;
    struct mem_req_info mem_req_arr[p_ref_len];
    std::cout<<"Enter Page Refrence Sequence : ";
    for(int i = 0; i < p_ref_len; i++)
    {
        scanf(" %d", &mem_req_arr[i].p_id);
        mem_req_arr[i].in_time = -1;
    }
    
    struct mem_req_info mem_currently_in_use__cache[f_size];
    for(int i = 0; i < f_size; i++)
    {
        mem_currently_in_use__cache[i].in_time = -1;
        mem_currently_in_use__cache[i].p_id = -1;
    }
    mem_currently_in_use__cache[0] = mem_req_arr[0];
    mem_currently_in_use__cache[0].in_time = 0;
    int replacement_index = 0;
    page_fault++;
    int processes_arr_no = 1;
    int init_index = 1;
    for (int i = 0; i < f_size; i++)
    {
        std::cout << "Process ID = " << mem_currently_in_use__cache[i].p_id << " Last Used Time = " << mem_currently_in_use__cache[i].in_time << std::endl;
    }
    std::cout<<std::endl;
    for(int time = 1; processes_arr_no < p_ref_len  ; time++)
    {
        if(!is_current_process_in_cache(mem_currently_in_use__cache, f_size, mem_req_arr[processes_arr_no]) && all_used(mem_currently_in_use__cache, f_size))
        {
            mem_currently_in_use__cache[replacement_index] = mem_req_arr[processes_arr_no];
            mem_currently_in_use__cache[replacement_index].in_time = time;
            page_fault++;
            replacement_index++;
        }
        else if(!is_current_process_in_cache(mem_currently_in_use__cache, f_size, mem_req_arr[processes_arr_no]))
        {
            mem_currently_in_use__cache[init_index] = mem_req_arr[processes_arr_no];
            mem_currently_in_use__cache[init_index++].in_time = time;
            page_fault++;
        }
        if(replacement_index >= f_size)
        {
            replacement_index = 0;
        }
        for (int i = 0; i < f_size; i++)
        {
            std::cout << "Process ID = " << mem_currently_in_use__cache[i].p_id << " Last Used Time = " << mem_currently_in_use__cache[i].in_time << std::endl;
        }
        std::cout<< std::endl;
        processes_arr_no++;
    }
    
    std::cout<<std::endl<<"Processes Left in Cache after all of Page refrence Sequence is evaluated : "<<std::endl;
    for(int i = 0; i < f_size; i ++)
    {
        std::cout<<"Process ID = "<<mem_currently_in_use__cache[i].p_id<<" Last Used Time = "<<mem_currently_in_use__cache[i].in_time<<std::endl;
    }
    std::cout<<"Total Page Faults = "<<page_fault<<std::endl;
    return 0;
}

// rutvik1999@Rutvik1999s-MacBook-Pro:~/OneDrive/OS_Lab/Sem 5 OS Lab$ cd "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/" && g++ -std=c++11 Page_replacement_FIFO.cpp -o Page_replacement_FIFO && "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/"Page_replacement_FIFO
// Enter Frame Size : 3
// Enter Page refrence (Sequence) Length : 7
// Enter Page Refrence Sequence : 1 3 0 3 5 6 3
// Process ID = 1 Last Used Time = 0
// Process ID = -1 Last Used Time = -1
// Process ID = -1 Last Used Time = -1

// Process ID = 1 Last Used Time = 0
// Process ID = 3 Last Used Time = 1
// Process ID = -1 Last Used Time = -1

// Process ID = 1 Last Used Time = 0
// Process ID = 3 Last Used Time = 1
// Process ID = 0 Last Used Time = 2

// Process ID = 1 Last Used Time = 0
// Process ID = 3 Last Used Time = 1
// Process ID = 0 Last Used Time = 2

// Process ID = 5 Last Used Time = 4
// Process ID = 3 Last Used Time = 1
// Process ID = 0 Last Used Time = 2

// Process ID = 5 Last Used Time = 4
// Process ID = 6 Last Used Time = 5
// Process ID = 0 Last Used Time = 2

// Process ID = 5 Last Used Time = 4
// Process ID = 6 Last Used Time = 5
// Process ID = 3 Last Used Time = 6


// Processes Left in Cache after all of Page refrence Sequence is evaluated : 
// Process ID = 5 Last Used Time = 4
// Process ID = 6 Last Used Time = 5
// Process ID = 3 Last Used Time = 6
// Total Page Faults = 6