#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define QUANTUM 2 //every 2 seconds 

typedef struct{
	int arrivaltime;
	int priority; 
	int processortime;
	int mbytes;
	int printers;
	int scanners;
	int modem;
	int cds;	
} Process;

typedef struct{
int available_mbytes; 
int available_printers;  
int available_scanners;  
int available_modem;     
int available_cds;  
} Resource;

typedef struct {
    int total;
    int *memorymap; // Represents memory blocks (1 = allocated, 0 = free)
} Memory;
			//dispatcher== file name
void fcfs (const char *dispatcher, Process *process, int num);//num == num of processes 
void dispatchlist(const char *file, Process *process, int *num);
void userfeedback(Process *process, int num);
void roundrobin(Process *process, int num);
void mixedsched(Process *process, int num);
void resourcealloc(Process *process, int num, Resource *resource);
void memorymanagement(Process *process, int num, Memory *memory);
void combo(Process *process, int num);


int main(){
	Process process[1000];
	int num =0;
	char dispatch[100];

	printf("Enter the address of the file 'Dispatcher List' ");
	scanf("%s", dispatch);

	dispatchlist(dispatch, process, &num);

	//fcfs (dispatch, process, num);
	//userfeedback(process, num);
	/*roundrobin(process, num);
	mixedsched(process, num);
	resourcealloc(process, num);
	memorymanagement(process, num);
	combo(process, num);*/

	return 0;
}

void dispatchlist(const char *file, Process *process, int *num) {
    FILE *File = fopen(file, "r");
    if (File == NULL) {
        printf("Error opening file: %s\n", file);
        perror("fopen");
        exit(1);
    }

    int result;
    while ((result = fscanf(File, "%d, %d, %d, %d, %d, %d, %d, %d", 
        &process[*num].arrivaltime,
        &process[*num].priority,
        &process[*num].processortime,
        &process[*num].mbytes,
        &process[*num].printers,
        &process[*num].scanners,
        &process[*num].modem,
        &process[*num].cds)) == 8) {
        printf("Arrival Time: %d, Priority: %d, Processor Time: %d, Memory: %d MB, Printers: %d, Scanners: %d, Modem: %d, CDs: %d\n",
            process[*num].arrivaltime,
            process[*num].priority,
            process[*num].processortime,
            process[*num].mbytes,
            process[*num].printers,
            process[*num].scanners,
            process[*num].modem,
            process[*num].cds);
        (*num)++;
		}
    fclose(File);
}


void fcfs (const char *dispatcher, Process *process, int num){
printf("FCFS for real-time processes:\n");
    for (int i = 0; i < num; i++) {
        printf("Arrival Time: %d, Priority: %d, Processor Time: %d, Memory: %d MB, Printers: %d, Scanners: %d, Modem: %d, CDs: %d\n",
            process[i].arrivaltime,
            process[i].priority,
            process[i].processortime,
            process[i].mbytes,
            process[i].printers,
            process[i].scanners,
            process[i].modem,
            process[i].cds);
    }
}

void userfeedback(Process *process, int num){
	Process FeedBackQueue[4][num];
	int qlenghts[4] = {0};

	for(int i = 0; i < num; i++) {
		int priority = process[i].priority;
		FeedBackQueue[priority][qlenghts[priority]] = process[i];
		qlenghts[priority]++;
	}
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < qlenghts[i]; j++){
			printf("%d, %d, %d, %d, %d, %d, %d, %d\n",
				FeedBackQueue[i][j].arrivaltime, 
				FeedBackQueue[i][j].priority,
            	FeedBackQueue[i][j].processortime, 
				FeedBackQueue[i][j].mbytes,
                FeedBackQueue[i][j].printers, 
				FeedBackQueue[i][j].scanners,
            	FeedBackQueue[i][j].modem, 
				FeedBackQueue[i][j].cds);
		}
	}
}


void roundrobin(Process *process, int num){
printf("Round Robin scheduler: ");
    int remain[num];
    for (int i = 0; i < num; i++) {
        remain[i] = process[i].processortime;
    }

    int current = 0;
    while (1) {
        int n = 1;
        for (int i = 0; i < num; i++) {
        if (remain[i] > 0) {
                n = 0;
                if (remain[i] > QUANTUM) {
                    current += QUANTUM;
                    remain[i] -= QUANTUM;
                    printf("Process %d is executing at time %d\n", i, current);
                } else {
                    current += remain[i];
                    printf("Process %d is executing at time %d\n", i, current);
                    remain[i] = 0;
                }
            }
        }
        if (n == 1) {
            break;
        }
    }
}

void mixedsched(Process *process, int num){
printf("Mixed Scheduling:\n");
printf("FCFS for real-time processes:\n");
    for (int i = 0; i < num; i++) {
        printf("Arrival Time: %d, Priority: %d, Processor Time: %d, Memory: %d MB, Printers: %d, Scanners: %d, Modem: %d, CDs: %d\n",
            process[i].arrivaltime,
            process[i].priority,
            process[i].processortime,
            process[i].mbytes,
            process[i].printers,
            process[i].scanners,
            process[i].modem,
            process[i].cds);
    }
	printf("Round-Robin scheduling for non-real-time processes:\n");
    int quantum = TIME_QUANTUM;
    while (1) {
        int done = 1; // Flag to check if all non-real-time processes are executed
        for (int i = 0; i < num; i++) {
            if (process[i].priority > 0 && process[i].processortime > 0) {
                done = 0; // There are pending non-real-time processes
                printf("Executing Process %d (Priority: %d)\n", i, process[i].priority);
                // Simulate execution of the process for the time quantum
                process[i].processortime -= TIME_QUANTUM;
                if (process[i].processortime < 0) {
                    process[i].processortime = 0; // Ensure process time doesn't go negative
                }
                // Check if process completed execution
                if (process[i].processortime == 0) {
                    printf("Process %d completed execution.\n", i);
                }
            }
        }
        if (done) {
            break; // All non-real-time processes have completed execution
        }
    }
	
    }

    // Round-Robin scheduling for non-real-time processes (priority > 0)
    printf("Round-Robin scheduling for non-real-time processes:\n");
    int quantum = TIME_QUANTUM;
    while (1) {
        int done = 1; // Flag to check if all non-real-time processes are executed
        for (int i = 0; i < num; i++) {
            if (process[i].priority > 0 && process[i].processortime > 0) {
                done = 0; // There are pending non-real-time processes
                printf("Executing Process %d (Priority: %d)\n", i, process[i].priority);
                // Simulate execution of the process for the time quantum
                process[i].processortime -= TIME_QUANTUM;
                if (process[i].processortime < 0) {
                    process[i].processortime = 0; // Ensure process time doesn't go negative
                }
                // Check if process completed execution
                if (process[i].processortime == 0) {
                    printf("Process %d completed execution.\n", i);
                }
            }
        }
        if (done) {
            break; // All non-real-time processes have completed execution
        }
    }
}

void resourcealloc(Process *process, int num, Resource *resource){
resource->available_mbytes = 1024; 
 resource->available_printers = 2;  
resource->available_scanners = 1;  
resource->available_modem = 1;     
resource->available_cds = 2;       

    printf("Resource Allocation:");

    for (int i = 0; i < num; i++) {
        if (process[i].mbytes <= resource->available_mbytes &&
            process[i].printers <= resource->available_printers &&
            process[i].scanners <= resource->available_scanners &&
            process[i].modem <= resource->available_modem &&
            process[i].cds <= resource->available_cds) {

	resource->available_mbytes -= process[i].mbytes;
            resource->available_printers -= process[i].printers;
            resource->available_scanners -= process[i].scanners;
            resource->available_modem -= process[i].modem;
            resource->available_cds -= process[i].cds;
            printf(" %d process allocated resources successfully ", i);
        } else {
            printf("allocation failed %d.\n", i);
        }
    }
}

void memorymanagement(Process *process, int num, Memory *memory){
	memory->total_memory = 2048; 
    memory->memory_map = (int *)malloc(memory->total_memory * sizeof(int));
    if (memory->memory_map == NULL) {
        printf("malloc failed.\n");
        exit(1);
    }

    for (int i = 0; i < memory->total_memory; i++) {
        memory->memory_map[i] = 0; 
    }

    printf("Memory Management:");

    for (int i = 0; i < num; i++) {
        int required = process[i].mbytes / 64; 
        int allocated = 0;

        for (int j = 0; j <= memory->total_memory - required; j++) {
            int count = 0;
            for (int k = j; k < j + required; k++) {
                if (memory->memory_map[k] == 0) {
                    count++;
                } else {
                    break; // Not enough contiguous free blocks
                }
            }
            if (count == required) {
                for (int k = j; k < j + required; k++) {
                    memory->memory_map[k] = 1;
                }
                printf("Process %d allocated memory blocks from %d to %d.\n", i, j, j +  - 1);
                allocated = 1;
                break;
            }
        }

        if (!allocated) {
            printf("malloc too low %d.\n", i);
        }
    }

    free(memory->memory_map);
	
}

void combo(Process *process, int num){
}
