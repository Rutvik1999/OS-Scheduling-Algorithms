#include <iostream>
#include <stdio.h>

struct mem_req_info
{
    int p_id, last_used_time;
};

void swap(struct mem_req_info *a, struct mem_req_info *b)
{
    struct mem_req_info temp = *a;
    *a = *b;
    *b = temp;
}

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

void shift_up(struct mem_req_info mem_currently_in_use__cache[], int f_size)
{
    for(int i = 0; i < f_size - 1; i++)
    {
        mem_currently_in_use__cache[i] = mem_currently_in_use__cache[i + 1]; 
    }
}

int get_index_from_p_id(struct mem_req_info arr[], int size, struct mem_req_info target)
{
    for(int i = 0; i < size; i++)
    {
        if(arr[i].p_id == target.p_id)
            return i;
    }
    return -1;
}

void sort_least_used(struct mem_req_info arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j].last_used_time > arr[j + 1].last_used_time)
                swap(&arr[j], &arr[j + 1]);
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
        mem_req_arr[i].last_used_time = -1;
    }
    
    struct mem_req_info mem_currently_in_use__cache[f_size];
    mem_currently_in_use__cache[f_size - 1] = mem_req_arr[0];
    mem_currently_in_use__cache[f_size - 1].last_used_time = 0;
    page_fault++;
    int processes_arr_no = 1;
    for (int i = 0; i < f_size; i++)
    {
        std::cout << "Process ID = " << mem_currently_in_use__cache[i].p_id << " Last Used Time = " << mem_currently_in_use__cache[i].last_used_time << std::endl;
    }
    std::cout << std::endl;
    for(int time = 1; processes_arr_no < p_ref_len  ; time++)
    {
        if (is_current_process_in_cache(mem_currently_in_use__cache, f_size, mem_req_arr[processes_arr_no]))
        {
            mem_currently_in_use__cache[get_index_from_p_id(mem_currently_in_use__cache, f_size, mem_req_arr[processes_arr_no])].last_used_time = time;
        }
        else if(!is_current_process_in_cache(mem_currently_in_use__cache, f_size, mem_req_arr[processes_arr_no]))
        {
            shift_up(mem_currently_in_use__cache, f_size);
            mem_currently_in_use__cache[f_size - 1] = mem_req_arr[processes_arr_no];
            mem_currently_in_use__cache[f_size - 1].last_used_time = time;
            page_fault++;
        }
        if(processes_arr_no >= f_size)
        {
            sort_least_used(mem_currently_in_use__cache, f_size);
        }
        for (int i = 0; i < f_size; i++)
        {
            std::cout << "Process ID = " << mem_currently_in_use__cache[i].p_id << " Last Used Time = " << mem_currently_in_use__cache[i].last_used_time << std::endl;
        }
        std::cout<< std::endl;
        processes_arr_no++;
    }
    
    std::cout<<std::endl<<"Processes Left in Cache after all of Page refrence Sequence is evaluated : "<<std::endl;
    for(int i = 0; i < f_size; i ++)
    {
        std::cout<<"Process ID = "<<mem_currently_in_use__cache[i].p_id<<" Last Used Time = "<<mem_currently_in_use__cache[i].last_used_time<<std::endl;
    }
    std::cout<<"Total Page Faults = "<<page_fault<<std::endl;
    return 0;
}

// rutvik1999@Rutvik1999s-MacBook-Pro:~/OneDrive/OS_Lab/Sem 5 OS Lab$ cd "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/" && g++ -std=c++11 Page_replacement_LRU.cpp -o Page_replacement_LRU && "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/"Page_replacement_LRU
// Enter Frame Size : 3
// Enter Page refrence (Sequence) Length : 7
// Enter Page Refrence Sequence : 1 3 0 3 5 6 3
// Process ID = 0 Last Used Time = 0
// Process ID = 0 Last Used Time = 0
// Process ID = 1 Last Used Time = 0

// Process ID = 0 Last Used Time = 0
// Process ID = 1 Last Used Time = 0
// Process ID = 3 Last Used Time = 1

// Process ID = 0 Last Used Time = 2
// Process ID = 1 Last Used Time = 0
// Process ID = 3 Last Used Time = 1

// Process ID = 1 Last Used Time = 0
// Process ID = 0 Last Used Time = 2
// Process ID = 3 Last Used Time = 3

// Process ID = 0 Last Used Time = 2
// Process ID = 3 Last Used Time = 3
// Process ID = 5 Last Used Time = 4

// Process ID = 3 Last Used Time = 3
// Process ID = 5 Last Used Time = 4
// Process ID = 6 Last Used Time = 5

// Process ID = 5 Last Used Time = 4
// Process ID = 6 Last Used Time = 5
// Process ID = 3 Last Used Time = 6


// Processes Left in Cache after all of Page refrence Sequence is evaluated : 
// Process ID = 5 Last Used Time = 4
// Process ID = 6 Last Used Time = 5
// Process ID = 3 Last Used Time = 6
// Total Page Faults = 4