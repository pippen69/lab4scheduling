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


			//dispatcher== file name
//void fcfs (const char *dispatcher, Process *process, int num);//num == num of processes 
void dispatchlist(const char *file, Process *process, int *num);
void userfeedback(Process *process, int num);
/*void roundrobin(Process *process, int num);
void mixedsched(Process *process, int num);
void resourcealloc(Process *process, int num);
void memorymanagement(Process *process, int num);
void combo(Process *process, int num);*/


int main(){
	Process process[1000];
	int num;
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
}

void resourcealloc(Process *process, int num){
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

void memorymanagement(Process *process, int num){
	
}

void combo(Process *process, int num){
}

