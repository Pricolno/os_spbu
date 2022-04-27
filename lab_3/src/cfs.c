#include <stdio.h>
#include "../include/heap.h"


static const int prio_to_weight[40] = {
/* -20 */ 88761, 71755, 56483, 46273, 36291,
/* -15 */ 29154, 23254, 18705, 14949, 11916,
/* -10 */ 9548, 7620, 6100, 4904, 3906,
/* -5 */ 3121, 2501, 1991, 1586, 1277,
/* 0 */ 1024, 820, 655, 526, 423,
/* 5 */ 335, 272, 215, 172, 137,
/* 10 */ 110, 87, 70, 56, 45,
/* 15 */ 36, 29, 23, 18, 15,
};




int n = 0, sum_nice = 0;

int main(int argc, char** argv){
	printf("Hello world!\n");
	FILE* input_file = NULL;
	if(argc > 1) input_file = fopen(argv[1], "r");
	else input_file = fopen("input.txt", "r");
	
	if (input_file == NULL) {
        printf("Input file not found!\n");
        return 1;
    }

    FILE * output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Output file not found!\n");
        return 2;
    }
    
    
    int vruntime_now = 0, id_now, nice_now, actual_runtime_now, runtime_now;

    struct Heap* hp = create_heap();
    while (fscanf(input_file, "%d %d %d", &id_now, &nice_now,&runtime_now) == 3) {
        struct process* pr = create_process(vruntime_now, id_now, nice_now, actual_runtime_now, runtime_now);
        add(hp, pr);
        sum_nice += prio_to_weight[nice_now + 20];
        n++;
    }

    
     while (n > 0) {
        int min_granularity = 6;
        int sched_latency = 48; 


        struct process* cur = get_min(hp);
        //int cur_vruntime = cur->vruntime;
        // cur_id = cur->id;
        //   cur_nice = cur->nice, cur_actual_runtime = cur->actual_runtime, cur_total_runtime = cur->total_runtime;
        

        int time_slice = prio_to_weight[cur->nice + 20] * sched_latency / sum_nice;

        
        if (time_slice > cur->runtime - cur->actual_runtime) {
            time_slice = cur->runtime - cur->actual_runtime;
        }
        
        if (time_slice < min_granularity) {
            time_slice = min_granularity;
        }

        int new_vruntime = cur->vruntime + prio_to_weight[20] / prio_to_weight[cur->nice + 20] * time_slice;
        int new_actual_runtime = cur->actual_runtime + time_slice;
        
        fprintf(output_file, "Process %d will work %d ms\n", cur->id, time_slice);

        if (new_actual_runtime >= cur->runtime) {
            fprintf(output_file, "Process %d completed successfully\n", cur->id);
            n--;
            sum_nice -= prio_to_weight[cur->nice + 20];
        } else {
            struct process* pr = create_process(new_vruntime, cur->id, cur->nice, new_actual_runtime, cur->runtime);
            add(hp, pr);
        }
        
    }


	return 0;
}