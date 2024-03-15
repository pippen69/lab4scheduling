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
	Process process[10000];
	int num;
	char dispatch[1000];

	printf("Enter the address of the file 'Dispatcher List' ");
	scanf("%s", dispatch);

	dispatchlist(dispatch, process, &num);

	//fcfs (dispatch, process, num);
	userfeedback(process, num);
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
        printf("Error opening file.\n");
        exit(1);
    }

    while (fscanf(File, "%d,%d,%d,%d,%d,%d,%d,%d", 
		&process[*num].arrivaltime,
		&process[*num].priority,
		&process[*num].processortime,
		&process[*num].mbytes,
		&process[*num].printers,
		&process[*num].scanners,
		&process[*num].modem,
		&process[*num].cds) != EOF) {
        (*num)++;
    }
    fclose(File);
}

//void fcfs (const char *dispatcher, Process *process, int num){}

void userfeedback(Process *process, int num){
	Process FeedBackQueue[3][num];
	int qlenghts[3] = {0};

	for(int i = 0; i < num; i++) {
		int priority = process[i].priority;
		FeedBackQueue[priority][qlenghts[priority]] = process[i];
		qlenghts[priority]++;
	}
	for(int i = 0; i < num; i++) {
		printf("Priority %d feedback queue:\n", i);
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

void resourcealloc(Process *process, int num){
}

void memorymanagement(Process *process, int num){
}

void combo(Process *process, int num){
}
*/
