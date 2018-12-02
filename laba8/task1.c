#include <time.h>
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

int thread_count = 10;
int edit_count = 2;
long glob_var = 0;

void * inc(void * arg){
	for(int i = 0; i < edit_count; i++){
		fprintf(stdout, "ID: %lu VAR: %ld\n", pthread_self(), ++glob_var);
		usleep(15000);
	}
	return NULL;
}

void * dec(void * arg){
	for(int i = 0; i < edit_count; i++){
		fprintf(stdout, "ID: %lu VAR: %ld\n", pthread_self(), --glob_var);
		usleep(15000);
	}
	return NULL;
}


void parsearg(int argc, char ** argv){
	int res;
	const struct option long_opt[] = {
		{"help", 0, NULL, 'h'},
		{"thread",1, NULL, 't'},
		{"edit", 1, NULL, 'e'},
		{NULL, 0, NULL, 0}
	};	
	while((res = getopt_long(argc, argv, "ht:e:", long_opt, NULL)) != -1){
		switch(res){
			case 'h':
				fprintf(stdout, "-t | --therad [int]\tthread_count\n");
				break;
			case 't':
				thread_count = atoi(optarg);
				break;
			case 'e':
			    printf("e\n");
				edit_count = atoi(optarg);
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
	pthread_t *arr = malloc(thread_count * sizeof(pthread_t));
	for(int i = 0; i < thread_count; i++){
		if(i & 1){	
			s = pthread_create(&arr[i], NULL, inc, NULL);
		}else{
			s = pthread_create(&arr[i], NULL, dec, NULL);
		}
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
	fprintf(stdout, "VAR: %ld\n", glob_var);
	return EXIT_SUCCESS;
}
