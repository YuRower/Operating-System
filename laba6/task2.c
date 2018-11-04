#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h> 

#define MAX 4

struct thread_arg{
	char * name;
	char * str;
	int num;
};

void * func(void * arg){
	struct thread_arg targ =*(struct thread_arg *) arg;
	for (int i = 0; i < targ.num; i++)
		fprintf(stderr, "Thread %s. Str %s\t%d\n", targ.name, targ.str, i + 1);
	return NULL;
}

int main(void){	
	struct thread_arg arg[] = { {"thread1", "str1", 1}, {"thread2", "str2", 2}, {"thread3", "str3", 3},  {"thread4", "str4", 4} };
	pthread_t thread[MAX];
	for(int i = 0; i < MAX; i++){
		if (pthread_create(&thread[i], NULL, func, &arg[i])) {
			fprintf(stderr, "Error (thread%d)\n", i + 1);
		}
	}
	while(1);
	return EXIT_SUCCESS;
}