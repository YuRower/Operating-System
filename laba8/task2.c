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

double res = 0.0, a = 0.0, b = 2, h;
int n = 10000, loc_n;
pthread_mutex_t mut;
int thread_count;

double f(double x){
	return 4-x*x;
}

double integate(double loc_a, double loc_b){
	double integ = (f(loc_a) + f(loc_b)) * 0.5, x = loc_a;
	for (int i = 1; i <= loc_n - 1; ++i){
		x = loc_a + i * h;
		integ += f(x);
	}	
	integ = integ * h;
	return integ;
}

void * func(void * arg){
	double loc_a, loc_b, ans;
	int i = (int) arg;
	loc_a = a + i * loc_n * h;
	loc_b = loc_a + loc_n * h;
	ans = integate(loc_a, loc_b);
	pthread_mutex_lock(&mut);
	res += ans;
	fprintf(stdout, "thread id %lu: \t%g   \n", pthread_self(),res);
	pthread_mutex_unlock(&mut);
	return NULL;
}


void parsearg(int argc, char ** argv){
	int res;
	const struct option long_opt[] = {
		{"help", 0, NULL, 'h'},
		{"pthread",1, NULL, 'p'},
		{NULL, 0, NULL, 0}
	};	
	while((res = getopt_long(argc, argv, "hp:", long_opt, NULL)) != -1){
		switch(res){
			case 'h':
				fprintf(stdout, "-p | --ptherad [int]\tthread_count\n");
				exit(-1);
				break;
			case 'p':
				thread_count = atoi(optarg);
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
	int s;
	h = (b - a) / n;
	loc_n = n / thread_count;
	pthread_t * arr = malloc(thread_count * sizeof(pthread_t));
	s = pthread_mutex_init(&mut, NULL);
	if(s) {
		on_error();
	}
	for(int i = 0; i < thread_count; i++){
		s = pthread_create(&arr[i], NULL, func, (void*) i);
		if(s) {
		on_error();
	}
	}

	for(int i = 0; i < thread_count; i++){
		s = pthread_join(arr[i], NULL);
		if(s) {
		on_error();
	}
	}

	fprintf(stdout, "INTEGRAL: %g\n", res);
	pthread_mutex_destroy(&mut);
	free(arr);
	
	return EXIT_SUCCESS;
}
