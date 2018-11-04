#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>

void print_info(int var) {
	printf("INFO\n");
fprintf(stdout, "var = %d , var_addr = %p \npid = %d,ppid = %d \n",  (var), &(var),getpid(),getppid());
}
int main(int argc, char ** argv){
	int local_var = 0;
	pid_t pid = fork();
	local_var++;
	print_info(local_var);
	if(pid){
		fprintf(stdout, "Родительский процесс, pid потомка %d\n", pid);
		fork();
		++local_var;
		print_info(local_var);
		printf("окончил род процесс pid = %d\n ",getpid());
	}
	else if (!pid){
		fprintf(stdout, "Процесс - потомок\n");
		fork();
		++local_var;
		print_info(local_var);
		printf("окончил доч процесс pid = %d\n ",getpid());

	}
	return 0;
}
