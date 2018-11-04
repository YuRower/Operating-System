#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h> 


int get_rand_range_int(const int min, const int max) {
    return rand() % (max - min + 1) + min;
}

void print_info(char * str) {	
    srand(time(NULL));												
	for(int i = 0; i < 10; i++)	{																	
		fprintf(stderr, "%s Thread. Iteration: %d\n", (str), i + 1); 	
			sleep(get_rand_range_int(0, 2));												
	}
}

void * thread_func(void * arg){
	print_info("Child");
	return NULL;
}

int main(void){
//char buf[BUFSIZ];
//setbuf(stdout, buf);
pthread_t thread;
	int res;
	res = pthread_create(&thread, NULL, thread_func, NULL);
	if(res != 0){
		fprintf(stderr, "Error\n");
		return EXIT_FAILURE;
	}

	print_info("Main");
	//while(1);
	return EXIT_SUCCESS;
}