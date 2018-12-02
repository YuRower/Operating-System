#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIGNAL_COUNT 10

extern const char * const sys_siglist[];

void my_handler(int signo, siginfo_t *info, void *extra){
		fprintf(stdout, "PID: %d, signal: %s, value: [%d]\n", getpid(), sys_siglist[signo], info->si_value.sival_int);
}

int main(void){	
	struct sigaction action;
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = my_handler;

	sigaction(SIGUSR1, &action, NULL);
	//sigaction(SIGTERM, &action, NULL);

	pid_t child_pid = fork();
	if(child_pid == 0){
		while(1){
			printf("child_pid = %d \n",child_pid);
			pause();
		}
	}
	else{
		for(int i = 0; i < SIGNAL_COUNT; i++){
			union sigval v;
			v.sival_int = i;
			printf("Send from parent to child value %i\n", i);

			int res = sigqueue(child_pid, SIGUSR1, v);
			strerror(errno);
		}
		int status;
		sigqueue(child_pid, SIGTERM, (const union sigval) NULL);
		//kill(child_pid,SIGTERM);
		wait(&status);
		if (WIFEXITED(status)) 
        	printf("Exit status: %d\n", WEXITSTATUS(status)); 
    	else if (WIFSIGNALED(status)) 
       		psignal(WTERMSIG(status), "Exit signal"); 
		fprintf(stdout, "Parent PID: %d, Child PID: %d\n", getpid(), child_pid);
	}
	
	return EXIT_SUCCESS;
}