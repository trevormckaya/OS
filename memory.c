#include "oslabs.h"

struct MEMORY_BLOCK build_mblock(int start_address, int end_address, int segment_size, int process_id){
  struct MEMORY_BLOCK block;
  block.start_address = start_address;
  block.end_address = end_address;
  block.segment_size = segment_size;
  block.process_id = process_id;
  return block;
}

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
  int best_index = -1;
  int best_space = 99999;
  for(int i = 0; i < *map_cnt; i++){
    if(memory_map[i].segment_size >= request_size && memory_map[i].segment_size < best_space){
      best_index = i;
      best_space = memory_map[i].segment_size;
    }
  }
  if(best_index >= 0){
    if(memory_map[best_index].segment_size > request_size){
      memory_map[*map_cnt].start_address = memory_map[best_index].start_address + request_size;
      memory_map[*map_cnt].end_address = memory_map[best_index].end_address;
      memory_map[*map_cnt].process_id = 0;
      memory_map[*map_cnt].segment_size = memory_map[best_index].segment_size - request_size;
      memory_map[best_index].segment_size = request_size;
      memory_map[best_index].end_address = memory_map[best_index].start_address + request_size;
      memory_map[best_index].process_id = process_id;
      
      (*map_cnt)++;
      return memory_map[best_index];
    } else {
      memory_map[best_index].process_id = process_id;
      return memory_map[i];
    }
  } else {
    return build_mblock(0,0,0,0);
  }
}  
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){}  
struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){}
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address){}
