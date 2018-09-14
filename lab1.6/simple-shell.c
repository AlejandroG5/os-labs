#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


#define MAX_LINE		80 /* 80 chars per line, per command */

int value = 5;
int main(void){
	char args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    	int should_run = 1;
	int i, upper;
	pid_t pid;
	
	while (should_run){   
	        printf("osh>");
		fgets(args, MAX_LINE,stdin);
		pid= fork();
		
		if (pid == 0) { /* child process */
			char * a[MAX_LINE]={"/bin/bash","-c",args};
			execvp(a[0],a);
			return 0;
		}
		else if (pid > 0) { /* parent process */
			int i;
			int control;
			control=0;
			char *pch;
			if(!strchr(args,'&')){
				wait(NULL);
			}
		}		
	}
}



