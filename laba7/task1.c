#include <time.h>
#include <stdio.h>
#include <unistd.h> 
#include <getopt.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count = 0;
int * glob_arr = NULL;

typedef struct {
	int num;
} args_t;

int on_error(void){ 
	fprintf(stderr, "Error\n"); 
	return EXIT_FAILURE;		
}

int get_rand_range_int(const int min, const int max) {
	srand(time(NULL));
    return rand() % (max - min + 1) + min;
}

void * func(void * arg){
	args_t args = *((args_t*) arg);
	fprintf(stdout, "THREAD %d; sleep %d\n", args.num, args.num);
	sleep(args.num);
	glob_arr[args.num] = get_rand_range_int(1, 10);
	fprintf(stdout, "THREAD %d; sleep %d\n", args.num, glob_arr[args.num]);
	sleep(glob_arr[args.num]);
	return NULL;
}

void * thread_detach_func(void * arg){
	while(1){
		int cnt = 0;
		fprintf(stdout, "THREAD DETACHED:\n");
		fprintf(stdout, "Contents of array :\n");
		for(int i = 0; i < thread_count; i++){
			if(glob_arr[i])
				cnt++;
			fprintf(stdout, "%d ", glob_arr[i]);
		}
		printf("\n");
		if(cnt == thread_count) 
			break;
		sleep(1);
	}
	return NULL;
}

args_t * gen_args(int n){
	args_t * res = malloc(sizeof(args_t));
	res->num = n;
	return res;
}



void parsearg(int argc, char ** argv){
	int res;
	const struct option long_opt[] = {
		{"help", 0, NULL, 'h'},
		{"num",1, NULL, 'n'},
		{NULL, 0, NULL, 0}
	};	
	while((res = getopt_long(argc, argv, "hn:", long_opt, NULL)) != -1){
		switch(res){
			case 'h':
				fprintf(stdout, "-n | --num [int]\tthread_count\n");
				break;
			case 'n':
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
	pthread_t * arr = (pthread_t *) malloc(thread_count * sizeof(pthread_t));
	glob_arr = (int*) calloc(thread_count, sizeof(int));
	pthread_attr_t attr;
	pthread_t thread_detach;
	pthread_attr_init (&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	for(int i = 0; i < thread_count; i++){
		if(!i){
			fprintf(stdout, "Launch DETACHED). thread :\n");
			if(pthread_create(&thread_detach, &attr, &thread_detach_func, NULL)){
				on_error();
			}
		}
		if(pthread_create(&arr[i], NULL, &func, gen_args(i))){
			on_error();
		}
		
	}
	for(int i = 0; i < thread_count; i++)
		if(pthread_join(arr[i], NULL)){
			on_error();
	
		}
	pthread_attr_destroy (&attr);
	fprintf(stdout, "Main Thread. (end-of-all)\n");
	return EXIT_SUCCESS;
}
