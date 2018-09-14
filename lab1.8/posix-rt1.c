/**
 * A simple pthread program illustrating RT pthread scheduling.
 *
 * Figure 6.20
 *
 * To compile:
 *
 *	gcc posix-rt.c -o posix-rt -lpthread
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#define MAX_LINE 80

typedef struct {
    int id;
    int iteration;
}threads;

/* the thread runs in this function */
void *runner(void *param); 

main(int argc, char *argv[])
{
	int NUM_THREADS;
	char args[MAX_LINE /2 + 1];
	fgets(args, MAX_LINE ,stdin);
	NUM_THREADS=atoi(args);	
	threads tg [NUM_THREADS];
	int i, policy;
	pthread_t tid[NUM_THREADS]; 	/* the thread identifier */
	pthread_attr_t attr; 		/* set of attributes for the thread */

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* get the current scheduling policy */
	if (pthread_attr_getschedpolicy(&attr,&policy) != 0)
		fprintf(stderr, "Unable to get policy.\n");
	else {
		if (policy == SCHED_OTHER)
			printf("SCHED_OTHER\n");
		else if (policy == SCHED_RR)
			printf("SCHED_OTHER\n");
		else if (policy == SCHED_FIFO)
			printf("SCHED_FIFO\n");
	}
	
	/* set the scheduling policy - FIFO, RT, or OTHER */
	if (pthread_attr_setschedpolicy(&attr, SCHED_OTHER) != 0)
		printf("unable to set scheduling policy to SCHED_OTHER \n");

	/* create the threads */
	for (i = 0; i < NUM_THREADS; i++) {
		tg[i].id=i;
		tg[i].iteration=rand()%20;
		printf("Hello! I'm father! Created thread (%d) in interation: %d\n",tg[i].id,tg[i].iteration);
		pthread_create(&tid[i],&attr,runner,(void*)&tg[i]);
	}
	/**
	 * Now join on each thread
	 */
	for (i = 0; i < NUM_THREADS; i++) 
		pthread_join(tid[i], NULL);
}

/**
 * The thread will begin control in this function.
 */
void *runner(void *param) 
{
	/* do some work ... */
	long tid;
	long titeration;
	threads * t=param;
	tid= (long)t->id;
	titeration=(long)t->iteration;
	printf("Hello from thread %ld - I was created in interation %ld\n", tid, titeration);
	pthread_exit(0);
}
