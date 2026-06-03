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
    if(test_null_pcb(current_process)){
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
{}
struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp)
{}
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{}
struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
{}
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum)
{}
