#input : 8 15 23 35 44 56 68 78 89
def seek_min_diff(seek_req_arr_temp, prev_head_pos):
    diff_arr = [(i - prev_head_pos) for i in seek_req_arr_temp]
    diff_arr_abs = [abs(i) for i in diff_arr]
    min_diff_index_list = [i for i, j in enumerate(diff_arr_abs) if j == min(diff_arr_abs)]
    min_diff = diff_arr[min_diff_index_list[0]] + prev_head_pos
    if len(min_diff_index_list) == 1:
        return min_diff
    elif len(min_diff_index_list) > 1:
        r_count = l_count = 0
        for i in seek_req_arr_temp:
            if i < min_diff:
                l_count +=1
            if i > min_diff:
                r_count +=1
        if l_count > r_count or l_count == r_count:
            diff_arr_return_index = min_diff_index_list[0]
        elif l_count < r_count:
            diff_arr_return_index = min_diff_index_list[-1]
        min_diff = diff_arr[diff_arr_return_index] + prev_head_pos
    return min_diff

def main():
    initial_head_pos = int(input("Enter Initial Head Position : "))
    tot_seek_operations = int(input("Enter total number of seek operations : "))
    print("Enter Seek Requests (in order) : ")
    seek_req_arr = list(map(int,list(input().split(" "))))
    if(len(seek_req_arr) != tot_seek_operations):
        raise Exception("Invalid input")
    read_sequence = []
    seek_req_arr_temp = seek_req_arr
    read_sequence.append(initial_head_pos)
    prev_head_pos = initial_head_pos
    for i in range(len(seek_req_arr)):
        if i not in read_sequence:
            current_track = seek_min_diff(seek_req_arr_temp, prev_head_pos)
            read_sequence.append(current_track)
            prev_head_pos = current_track
            seek_req_arr_temp.remove(current_track)
    seek_time = 0
    prev_seek = initial_head_pos
    for i in range(0, len(read_sequence)):
        seek_time = seek_time + abs(read_sequence[i] - prev_seek)
        prev_seek = read_sequence[i]
        
    print("Start Position : " + str(read_sequence[0]))
    print("Seek Sequence :")
    print(read_sequence[1:])
    print("Total Seek time = " + str(seek_time))
    
if __name__ == "__main__":   
    try:
        main()
    except Exception as ex:
        print(ex)
        

# rutvik1999@Rutvik1999s-MacBook-Pro:~$ python3 -u "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/SSTF.py"
# Enter Initial Head Position : 53
# Enter total number of seek operations : 8
# Enter Seek Requests (in order) : 
# 98 183 41 122 14 124 65 67
# Start Position : 53
# Seek Sequence :
# [65, 67, 41, 14, 98, 122, 124, 183]
# Total Seek time = 236

# rutvik1999@Rutvik1999s-MacBook-Pro:~$ python3 -u "/Users/rutvik1999/OneDrive/OS_Lab/Sem 5 OS Lab/SSTF.py"
# Enter Initial Head Position : 50
# Enter total number of seek operations : 8
# Enter Seek Requests (in order) : 
# 176 79 34 60 92 11 41 114
# Start Position : 50
# Seek Sequence :
# [41, 34, 11, 60, 79, 92, 114, 176]
# Total Seek time = 204
#4 34 10 7 19 73 2 15 6 20
