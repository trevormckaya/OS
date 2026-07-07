#include "oslabs.h"

int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    
    if(page_table[page_number] == 1){
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count += 1;
    } else if (*frame_cnt > 0){
        *frame_cnt = *frame_cnt - 1;
        page_table[page_number].frame_number = frame_pool[*frame_cnt];
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
    } else {
        int min_arrival_timestamp = 9999999;
        int min_arrival_index = 0;
        for(int i = 0; i < *table_cnt; i++)
        {
            if(page_table[i].is_valid == 1 && min_arrival_timestamp > page_table[i].arrival_timestamp)
            {
                min_arrival_timestamp = page_table[i].arrival_timestamp;
                min_arrival_index = i;
            }
        }
        page_table[page_number].frame_number = frame_pool[*frame_cnt];
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
int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    //
}
int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    //
} 
int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    //
}
int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    //
} 
int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    //
}
