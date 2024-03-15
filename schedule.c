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
			
void fcfs (const char *dispatch.txt, Process *process, int num);//num == number of processes 
void userfeedback(Process *process, int num);
void roundrobin(Process *process, int num);
void mixedsched(Process *process, int num);
void resourcealloc(Process *process, int num);
void memorymanagement(Process *process, int num);
void combo(Process *process, int num);


int main(){
Process process;

printf("Enter the address of the file 'Dispatcher List' ");
scan ("%s", dispatch.txt);

dispatchlist(dispatch.txt, process, &num);

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
printf("FCFS for real-time process");
for (int i = 0; i < num; i++){
if (process[i].priority == 0){
printf("Job %d: arrival time: %d, prirority: %d, requiring %d second(s) of CPU time and %d Mbytes memory. %d printer, %d scanners, %d modem, %d CD", i, arrivalime, priority, processortime, mbytes, printers, scanners, modem, cds);
}
}
}

void userfeedback(Process *process, int num){
printf("User Feedback scheduler ");
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



