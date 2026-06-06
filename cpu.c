#include "oslabs.h"
int test_null_pcb(struct PCB inpcb){
    if(inpcb.process_id == 0 && 
        inpcb.arrival_timestamp == 0 &&
        inpcb.total_bursttime == 0 &&
        inpcb.execution_starttime == 0 &&
        inpcb.execution_endtime == 0 &&
        inpcb.remaining_bursttime == 0 &&
        inpcb.process_priority == 0)
        return 1;
    else
        return 0;
}

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{
    if (test_null_pcb(current_process)){
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    } else if (new_process.process_priority >= current_process.process_priority){
        new_process.execution_starttime = 0;
        new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[*queue_cnt] = new_process;
        *queue_cnt += 1;
        return current_process;
    } else {
        current_process.execution_endtime = 0;
        current_process.remaining_bursttime -= timestamp - current_process.execution_starttime;
        ready_queue[*queue_cnt] = current_process;
        *queue_cnt += 1;
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }
}
struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{
    int index = 0;
    if (*queue_cnt == 0){
        return (struct PCB){0,0,0,0,0,0,0};
    } else {
        //find lowest priority value
        for (int i = 1; i < *queue_cnt; i++){
            if (ready_queue[i].process_priority < ready_queue[index].process_priority){
                index = i;
            }
        }
        //update timestamps for highest priority value
        ready_queue[index].execution_starttime = timestamp;
        ready_queue[index].execution_endtime = timestamp + ready_queue[index].remaining_bursttime;

        //store the next PCB for return
        struct PCB temp = ready_queue[index];
        
        //remove process from ready queue
        for (int i = index; i < *queue_cnt - 1; i++){
            ready_queue[i] = ready_queue[i + 1];
        }
        *queue_cnt -= 1;
        
        return temp;
    }
}
struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{
    if (test_null_pcb(current_process)) {
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    } else if (new_process.total_bursttime >= current_process.remaining_bursttime {
        new_process.execution_starttime = 0;
        new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[*queue_cnt] = new_process;
        *queue_cnt += 1;
        return current_process;
    } else {
        current_process.execution_endtime = 0;
        current_process.remaining_bursttime -= timestamp - current_process.execution_starttime;
        ready_queue[*queue_cnt] = current_process;
        *queue_cnt += 1;
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }
}
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{}
struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
{}
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum)
{}
