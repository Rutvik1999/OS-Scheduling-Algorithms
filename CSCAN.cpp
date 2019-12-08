#include <iostream>
#include <stdio.h>
#include <cstdlib>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}
int get_index_head_from_sorted_arr(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        if(arr[i] == 0)
            return i;
    }
    return -1;
}

int main()
{
    std::cout<<"Enter Initial Position of Head : ";
    int initial_head_pos;
    std::cin>>initial_head_pos;
    std::cout<<"Enter total number of Seek operations : ";
    int tot_seek_operations;
    std::cin>>tot_seek_operations;
    tot_seek_operations++;
    int max_track_lim;
    std::cout<<"Enter Maximum Track Number : ";
    std::cin>>max_track_lim;
    std::cout<<"Enter Seek Requests (in order) : ";
    int seek_req_arr[tot_seek_operations];
    for(int i = 0; i < tot_seek_operations - 1; i++)
    {
        scanf("%d",&seek_req_arr[i]);

    }
    seek_req_arr[tot_seek_operations - 1] = initial_head_pos;
    int diff_from_initial_pos_arr[tot_seek_operations];
    
    for (int i = 0; i < tot_seek_operations; i++)
    {
        diff_from_initial_pos_arr[i] = seek_req_arr[i] - initial_head_pos;
    }

    bubbleSort(diff_from_initial_pos_arr, tot_seek_operations);
    int head_pos_start_index = get_index_head_from_sorted_arr(diff_from_initial_pos_arr, tot_seek_operations);
    int read_sequence_final[tot_seek_operations + 2];
    int j = 0;
    for(int i = head_pos_start_index; i < tot_seek_operations; i++, j++)
    {
        read_sequence_final[j] = initial_head_pos + diff_from_initial_pos_arr[i];
    }
    read_sequence_final[j++] = max_track_lim;
    read_sequence_final[j++] = 0;
    for(int i = 0; i < head_pos_start_index; i++, j++)
    {
        read_sequence_final[j] = initial_head_pos + diff_from_initial_pos_arr[i];
    }
    int seek_time = 0;
    int prev_seek = initial_head_pos;
    for(int i = 0; i < tot_seek_operations + 2; i++)
    {
        seek_time = seek_time + abs(read_sequence_final[i] - prev_seek);
        prev_seek = read_sequence_final[i];
    }
    std::cout<<std::endl;
    std::cout<<"Start Position : "<<read_sequence_final[0]<<std::endl;
    std::cout<<"Seek Sequence :"<<std::endl;
    for(int i = 1; i < tot_seek_operations + 2; i++)
    {
        std::cout<<read_sequence_final[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Total Seek Time = "<<seek_time<<std::endl;
    return 0;
}

// rutvik1999@Rutvik1999s-MacBook-Pro:~/OneDrive/OS_Lab/Sem 5 OS Lab$ cd "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/" && g++ -std=c++11 CSCAN.cpp -o CSCAN && "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/"CSCAN
// Enter Initial Position of Head : 50
// Enter total number of Seek operations : 8
// Enter Maximum Track Number : 199
// Enter Seek Requests (in order) : 176 79 34 60 92 11 41 114

// Start Position : 50
// Seek Sequence :
// 60 79 92 114 176 199 0 11 34 41 
// Total Seek Time = 389