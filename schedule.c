#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

struct Process{
	int arrivaltime;
	int priority; 
	int processortime;
	int mbytes;
	int printers;
	int scanners;
	int modem;
	in cds;	
};
			//dispatcher== file name
void fcfs (const char *dispatcher, Process *process, int num);//num == number of processes 
void userfeedback(Process *process, int num);
void roundrobin(Process *process, int num);
void mixedsched(Process *process, int num);
void resourcealloc(Process *process, int num);
void memorymanagement(Process *process, int num);
void combo(Process *process, int num);


int main(){
Process process;

printf("Enter the address of the file 'Dispatcher List' ");
scan ("%s", dispatcher);

dispatchlist(dispatch, process, &num);

fcfs (process, num);
userfeedback(process, num);
roundrobin(process, num);
mixedsched(process, num);
resourcealloc(process, num);
memorymanagement(process, num);
combo(process, num);

return 0;
}


void fcfs (const char *dispatcher, Process *process, int num){
}

void userfeedback(Process *process, int num){
}

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


