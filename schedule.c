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

typedef struct {
    int printers;
    int scanners;
    int modem;
    int cds;
} Resources;

typedef struct {
    int total;
    int *memorymap;
} Memory;

//dispatcher== file name
void fcfs (const char *dispatcher, Process *process, int num);//num == num of processes 
void dispatchlist(const char *file, Process *process, int *num);
void userfeedback(Process *process, int num);
void roundrobin(Process *process, int num);
void mixedsched(Process *process, int num);
void resourcealloc(Process *process, int num, Resources *resources);
void memorymanagement(Process *process, int num, Memory *memory);
//void combo(Process *process, int num);*/


int main(){
	Process process[1000];
	Resources resources;
	Memory memory;
	int num;
	char dispatch[100];
	printf("\n");
	printf("Enter the address of the file 'Dispatcher List' ");
	scanf("%s", dispatch);

	dispatchlist(dispatch, process, &num);

	fcfs (dispatch, process, num);
	userfeedback(process, num);
	roundrobin(process, num);
	mixedsched(process, num);
	resourcealloc(process, num, &resources);
	memorymanagement(process, num, &memory);
	//combo(process, num);

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
        printf("%d, %d, %d, %d, %d, %d, %d, %d\n",
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
	printf("\nFirst Come First Serve function:\n");
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
	printf("\nUser Feedback function:\n");
	Process FeedBackQueue[4][num];
	int qlenghts[4] = {0};

	for(int i = 0; i < num; i++) {
		int priority = process[i].priority;
		FeedBackQueue[priority][qlenghts[priority]] = process[i];
		qlenghts[priority]++;
	}
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < qlenghts[i]; j++){
			printf("Arrival Time: %d, Priority: %d, Processor Time: %d, Memory: %d MB, Printers: %d, Scanners: %d, Modem: %d, CDs: %d\n",
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
	printf("\nRound Robin scheduler: ");
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
printf("\nMixed Scheduling:\n");
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
    int quantum = QUANTUM;
    while (1) {
        int done = 1; // Flag to check if all non-real-time processes are executed
        for (int i = 0; i < num; i++) {
            if (process[i].priority > 0 && process[i].processortime > 0) {
                done = 0; // There are pending non-real-time processes
                printf("Executing Process %d (Priority: %d)\n", i, process[i].priority);
                // Simulate execution of the process for the time quantum
                process[i].processortime -= QUANTUM;
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

void resourcealloc(Process *process, int num, Resources *resources) {
	printf("\nResource alloc function:\n");
	int i;
	for (i = 0; i < num; i++) {
        if (process[i].printers <= resources->printers && 
            process[i].scanners <= resources->scanners && 
            process[i].modem <= resources->modem && 
            process[i].cds <= resources->cds) {
            
            printf("Process %d can be allocated resources\n", i);
            
            resources->printers -= process[i].printers;
            resources->scanners -= process[i].scanners;
            resources->modem -= process[i].modem;
            resources->cds -= process[i].cds;
        } 
		else {
            printf("Process %d cannot be allocated\n", i);
        }
    }
}

void memorymanagement(Process *process, int num, Memory *memory){
	printf("\nmemory management function:\n");
	memory->total = 2048; 
    memory->memorymap = (int *)malloc(memory->total * sizeof(int));
    if (memory->memorymap == NULL) {
        printf("malloc failed.\n");
        exit(1);
    }

    for (int i = 0; i < memory->total; i++) {
        memory->memorymap[i] = 0; 
    }

    printf("Memory Management:");

    for (int i = 0; i < num; i++) {
        int required = process[i].mbytes / 64; 
        int allocated = 0;

        for (int j = 0; j <= memory->total - required; j++) {
            int count = 0;
            for (int k = j; k < j + required; k++) {
                if (memory->memorymap[k] == 0) {
                    count++;
                } else {
                    break; // Not enough contiguous free blocks
                }
            }
            if (count == required) {
                for (int k = j; k < j + required; k++) {
                    memory->memorymap[k] = 1;
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

    free(memory->memorymap);
}


//void combo(Process *process, int num){}
