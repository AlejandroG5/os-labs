#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAX_LINE 80

enum state {IDLE,READY,WAIT,RUN};
typedef struct{
	int burst_time;
	int id;
	int priority;
	int waiting_time;
	enum state state;
}process;




process pg[10];
process psjf[10];
int size=sizeof(pg)/sizeof(process);
int time1=0;
int quantum;
char args[MAX_LINE /2 + 1];
int counter=0;
int busy=1;

void createprocess(int,int,int);
void activate();
int pendingtasks();

int main(void){
	printf("Introduce the quantum number: ");
	fgets(args, MAX_LINE ,stdin);
	quantum=atoi(args);
	printf("%d\n",quantum);	
	srand(time(NULL));
	int m,a,b,i;
	for(m=0;m<size;m++){
		int p= rand()%50;
		if(p==0)p=1;
		int bt= rand()%10;
		if(bt==0)bt=1;
		createprocess(m,bt,p);
	}
	printf("Creatoion order: \n");
	for(i=0;i<size;i++){
		printf(" ID: %d STATE: %d priority: %d burst time: %d sec\n",pg[i].id , pg[i].state , pg[i].priority, pg[i].burst_time);
	}
	for(a=1;a<size;a++){
		time1+=pg[a-1].burst_time;
		pg[a].waiting_time=time1;
	}
	while(busy==1){
		if(pg[counter].burst_time!=0){		
			activate(counter);
		}
		counter++;
		if(counter==size){
			counter=0;
		}
		busy=pendingtasks();
	}
	printf("Average wait time: %d\n",(time1/size));
	return 0;
}

void createprocess(int id, int burst, int priority){
	pg[id].id=id;
	pg[id].burst_time=burst;
	pg[id].priority=priority;
	pg[id].state=READY;
}

void activate(int b){
	pg[b].state=RUN;
	int i;
	printf("Running %d", b);
	if(quantum<pg[b].burst_time){	
		pg[b].burst_time-=quantum;
		printf(" ID: %d STATE: %d priority: %d burst time: %d sec\n",pg[b].id , pg[b].state , pg[b].priority, pg[b].burst_time);
		pg[b].state=READY;
	}else{
		pg[b].burst_time=0;
		pg[b].state=IDLE;
		printf(" ID: %d STATE: %d priority: %d burst time: %d sec\n",pg[b].id , pg[b].state , pg[b].priority, pg[b].burst_time);
		printf("Finished task no. %d\n", b);
	}
}

int pendingtasks(){
	int control=0;
	int i;	
	for(i=0;i<size;i++){
		if(pg[i].burst_time!=0){
			control=1;
		}
	}
	return control;
}
