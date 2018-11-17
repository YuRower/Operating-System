#include <time.h>
#include <math.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h> 
#include <getopt.h>
#include <stdlib.h>
#include <pthread.h>

int on_error(void){ 
	fprintf(stderr, "Error\n"); 
	return EXIT_FAILURE;		
}

int DELAY_TIME = 0;


void * func(void * arg){
	int i = 1, n = 100000, old_cancel_state;
	long double pi, a, b;
	a = b = pi = 4.0;
	for(;i <= n; i++){
		printf("%d\n", i );
		/* Начало не отменяемой области */
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
			pi += a = (b = -b) / (2 * i + 1.0);   
			/* Конец не отменяемой области */
		pthread_setcancelstate(old_cancel_state, NULL);
		fprintf(stdout, "pi = %.10Lf\n", pi);
	}
	return NULL;
}

void parsearg(int argc, char ** argv)
{
	int res, ind;
	const char * short_opt = "hn:";
	const struct option long_opt[] = {
		{"help", 0, NULL, 'h'},
		{"num",1, NULL, 'n'},
		{NULL, 0, NULL, 0}
	};	
	while((res = getopt_long(argc, argv, short_opt, long_opt, &ind)) != -1){
		switch(res){
			case 'h':
				fprintf(stdout, "-n | --num [int]\tsleep sec\n");
				break;
			case 'n':
				DELAY_TIME = atoi(optarg);
				break;
			case '?':
				fprintf(stderr, "%s\n", "Unknown option");
				break;
			default:
				break;
		}
	}
}

int main(int argc, char ** argv){
	parsearg(argc, argv);
	pthread_t thread;
	int s;
	void * res;
	s = pthread_create(&thread, NULL, &func, NULL);
	if(s) on_error();
	sleep(DELAY_TIME);	
	s = pthread_cancel(thread);
	// if(s) handle_error_en(s, "main(): pthread_cancel");
	s = pthread_join(thread, &res);
	if (s) on_error();
	if (res == PTHREAD_CANCELED)
		printf("main(): thread was canceled\n");
	else
		printf("main(): thread wasn't canceled\n");
	return EXIT_SUCCESS;
}
