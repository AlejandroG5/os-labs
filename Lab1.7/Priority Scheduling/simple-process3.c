#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


enum state {IDLE,READY,WAIT,RUN};

typedef struct{
	int burst_time;
	int id;
	int priority;
	int waiting_time;
	enum state state;
}process;


void createprocess(int,int,int);
void insertionpriority();
void activateburst();

process pg[10];
process psjf[10];
int size=sizeof(pg)/sizeof(process);
int time1=0;
int main(void){
	srand(time(NULL));
	int m,a,b,i;
	for(m=0;m<size;m++){
		int p= rand()%50;
		int bt= rand()%100;
		createprocess(m,bt,p);
	}

	printf("Creatoion order: \n");
	for(i=0;i<size;i++){
		printf(" ID: %d STATE: %d priority: %d burst time: %d waiting time: %d sec\n",pg[i].id , pg[i].state , pg[i].priority, pg[i].burst_time, pg[i].waiting_time);
	}
	insertionpriority();
	for(a=1;a<size;a++){
		time1+=pg[a-1].burst_time;
		pg[a].waiting_time=time1;
	}
	for(b=0;b<size;b++){
		activateburst(b);
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

void activateburst(int b){
	pg[b].state=RUN;
	int i;
	//........ FUNCTIONALITIES OF EACH PROCESS
	printf("Running task no. %d\n", b);
	for(i=0;i<size;i++){
		printf(" ID: %d STATE: %d priority: %d burst time: %d waiting time: %d sec\n",pg[i].id , pg[i].state , pg[i].priority, pg[i].burst_time,pg[i].waiting_time);
	}
	pg[b].state=IDLE;
	printf("Finished task no. %d\n", b);
}
void insertionpriority(){
	int i, j;
	process key;
	for (i=1;i<size;i++){
		key = pg[i];
        	j = i-1;
       		while (j >= 0 && pg[j].priority > key.priority){
          		pg[j+1] = pg[j];
      	        	j = j-1;
        	}
        pg[j+1] = key;
	}
}
