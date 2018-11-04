#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h> 


struct thread_arg{
	int a;
	int  b;
	int c;
	int n;
};
/*const float RAND_MAX_F = RAND_MAX;
 
float get_rand() {
    return rand() / RAND_MAX_F;
}
float get_rand_range(const float min, const float max) {
    return get_rand() * (max - min) + min;
}*/

int get_rand_range_int(const int min, const int max) {
    return rand() % (max - min + 1) + min;
}
int on_error(void){ 
	fprintf(stderr, "Error\n"); 
	return EXIT_FAILURE;		
}
void print_info(char * str) {	
	for(int i = 0; i < 10; i++)	{																	
		fprintf(stderr, "%s Thread. Iteration: %d\n", (str), i + 1); 	
			sleep(get_rand_range_int(0, 2));												
	}
}

void * thread_func1(void * arg){
	print_info("Child1");
	return NULL;
}


void * thread_func2(void * arg){
	struct thread_arg targ =*(struct thread_arg *) arg;
	int target;
	srand(time(NULL));
	for(int i = 0; i < targ.n; i++){
		target = get_rand_range_int(targ.a, targ.b);
		fprintf(stdout, "Child2 Thread. Number: %d\n", target);
		if (target == targ.c){
			fprintf(stderr,"ERROR\n");
			pthread_exit(NULL);
		}
	}
	return NULL;
}

int main(void){
	pthread_t thread1, thread2;
	int num;
	printf("Enter a number :\n");
	scanf("%d", &num);
	struct thread_arg args = {1, 5, num,10};
	
	if(pthread_create(&thread1, NULL, thread_func1, NULL)){
		on_error();
	}

	if(pthread_create(&thread2, NULL, thread_func2, &args)){
		on_error();		
	}

	if(pthread_join(thread1, NULL)){
		fprintf(stderr, "Join1 error\n");
		return 1;
	}

	if (pthread_join(thread2, NULL)){
		fprintf(stderr, "Join2 error\n");
		return 1;
	}
	fprintf(stderr, "Main Thread have finished.\n");
	return EXIT_SUCCESS;
}