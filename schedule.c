#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

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

			//dispatcher== file name
//void fcfs (const char *dispatcher, Process *process, int num);//num == num of processes 
void dispatchlist(const char *file, Process *process, int *num);
void userfeedback(Process *process, int num);
void roundrobin(Process *process, int num);
void mixedsched(Process *process, int num);
void resourcealloc(Process *process, int num, Resources *resources);
void memorymanagement(Process *process, int num);
void combo(Process *process, int num);*/


int main(){
	Process process[1000];
	Resources resources;
	int num;
	char dispatch[100];

	printf("Enter the address of the file 'Dispatcher List' ");
	scanf("%s", dispatch);

	dispatchlist(dispatch, process, &num);

	fcfs (dispatch, process, num);
	userfeedback(process, num);
	roundrobin(process, num);
	mixedsched(process, num);
	resourcealloc(process, num, &resources);
	memorymanagement(process, num);
	combo(process, num);

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
        printf("arrival time: %d, priority: %d, processor time: %d, mbytes: %d, printers: %d, scanners: %d, modem: %d, cds: %d\n",
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


void fcfs (const char *dispatcher, Process *process, int num){}

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
/*
void roundrobin(Process *process, int num){
}

void mixedsched(Process *process, int num){
}
*/
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
/*
void memorymanagement(Process *process, int num){
}

void combo(Process *process, int num){
}
*/
