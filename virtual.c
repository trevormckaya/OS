
#include "oslabs.h"

int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    
    if(page_table[page_number].is_valid == 1){
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count += 1;
    } else if (*frame_cnt > 0){
        *frame_cnt -= 1;
        page_table[page_number].frame_number = frame_pool[*frame_cnt];
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
    } 
    else 
    {
        int min_arrival_timestamp = 999999;
        int min_arrival_index = 0;
        for(int i = 0; i < *table_cnt; i++)
        {
            if(page_table[i].is_valid == 1 && min_arrival_timestamp >= page_table[i].arrival_timestamp)
            {
                min_arrival_timestamp = page_table[i].arrival_timestamp;
                min_arrival_index = i;
            }
        }
        page_table[page_number].frame_number = page_table[min_arrival_index].frame_number;
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;

        page_table[min_arrival_index].frame_number = -1;
        page_table[min_arrival_index].is_valid = 0;
        page_table[min_arrival_index].arrival_timestamp = -1;
        page_table[min_arrival_index].last_access_timestamp = -1;
        page_table[min_arrival_index].reference_count = -1;
    }

    return page_table[page_number].frame_number;
} 
int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int reference_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    int page_faults = 0;
    //Check if page being referenced is already in memory (valid bit is true)
    for (int i = 0; i < reference_cnt; i++)
    {
        //If yes, update the last access timestamp and reference count
        if (page_table[reference_string[i]].is_valid == 0)
        {
            //Count page fault
            page_faults++;
        }
        //Process the page access using the FIFO page replacement algorithm
        process_page_access_fifo(page_table,&table_cnt,reference_string[i],frame_pool,&frame_cnt,i+1);
    }

    //return total number of page faults
    return page_faults;
}
int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    if(page_table[page_number].is_valid == 1){
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count += 1;
    } else if (*frame_cnt > 0){
        *frame_cnt -= 1;
        page_table[page_number].frame_number = frame_pool[*frame_cnt];
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
    }
    else {
        int min_last_access_timestamp = 999999;
        int min_last_access_index = 0;
        for(int i = 0; i < *table_cnt; i++){
            if(page_table[i].is_valid == 1 && min_last_access_timestamp >= page_table[i].last_access_timestamp){
                min_last_access_timestamp = page_table[i].last_access_timestamp;
                min_last_access_index = i;
            }
        }
        page_table[page_number].frame_number = page_table[min_last_access_index].frame_number;
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;  
        page_table[page_number].reference_count = 1;

        page_table[min_last_access_index].frame_number = -1;
        page_table[min_last_access_index].is_valid = 0;
        page_table[min_last_access_index].arrival_timestamp = -1;
        page_table[min_last_access_index].last_access_timestamp = -1;
        page_table[min_last_access_index].reference_count = -1;
    }

    return page_table[page_number].frame_number;

} 
int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int reference_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    int page_faults = 0;
    //Check if page being referenced is already in memory (valid bit is true)
    for (int i = 0; i < reference_cnt; i++)
    {
        //If yes, update the last access timestamp and reference count
        if (page_table[reference_string[i]].is_valid == 0)
        {
            //Count page fault
            page_faults++;
        }
        //Process the page access using the LRU page replacement algorithm
        process_page_access_lru(page_table,&table_cnt,reference_string[i],frame_pool,&frame_cnt,i + 1);
    }

    //return total number of page faults
    return page_faults;
}
int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    if(page_table[page_number].is_valid == 1){
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count += 1;
    } else if (*frame_cnt > 0){
        *frame_cnt -= 1;
        page_table[page_number].frame_number = frame_pool[*frame_cnt];
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
    }
    else {
        int min_reference_count = 999999;
        int min_reference_index = 0;
        for(int i = 0; i < *table_cnt; i++)
        {
            if(page_table[i].is_valid == 1 && 
                ((page_table[i].reference_count < min_reference_count) ||
                (page_table[i].reference_count == page_table[min_reference_index].reference_count && 
                page_table[i].arrival_timestamp < page_table[min_reference_index].arrival_timestamp)
                ))
            {
                min_reference_count = page_table[i].reference_count;
                min_reference_index = i;
            }
        }
        page_table[page_number].frame_number = page_table[min_reference_index].frame_number;
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;

        page_table[min_reference_index].frame_number = -1;
        page_table[min_reference_index].is_valid = 0;
        page_table[min_reference_index].arrival_timestamp = -1;
        page_table[min_reference_index].last_access_timestamp = -1;
        page_table[min_reference_index].reference_count = -1;
    }

    return page_table[page_number].frame_number;
} 
int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt, int reference_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    int page_faults = 0;
    //Check if page being referenced is already in memory (valid bit is true)
    for (int i = 0; i < reference_cnt; i++)
    {
        //If yes, update the last access timestamp and reference count
        if (page_table[reference_string[i]].is_valid == 0)
        {
            //Count page fault
            page_faults++;
        }
        //Process the page access using the LFU page replacement algorithm
        process_page_access_lfu(page_table,&table_cnt,reference_string[i],frame_pool,&frame_cnt,i + 1);
    }

    //return total number of page faults
    return page_faults;
}
