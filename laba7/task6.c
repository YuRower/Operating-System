#include <time.h>
#include <stdio.h>
#include <unistd.h> 
#include <getopt.h>
#include <stdlib.h>
#include <pthread.h>

int on_error(void){ 
	fprintf(stderr, "Error\n"); 
	return EXIT_FAILURE;		
}

int DELAY_TIME = 0;

void pthread_handler(void * arg){
	fprintf(stderr, "ON EXIT cleanup HANDELER\n");
}

void * func(void * arg){
	int i = 0, status;
	pthread_cleanup_push(pthread_handler, NULL);
	status = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	if(status){ 
		fprintf(stdout, "func(): pthread_setcancelstate ");
		on_error();
	}	while(1){
		fprintf(stdout, "func(): %d\n", i++);
		sleep(1);
	}
	pthread_cleanup_pop(1);
	return NULL;
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
	int status;
	status = pthread_create(&thread, NULL, &func, NULL);
	if(status){ 
		fprintf(stdout, "main(): pthread_create: \n");
		on_error();
	}
	sleep(DELAY_TIME);
	status = pthread_cancel(thread);
	if(status) {
		fprintf(stdout, "main(): pthread_cancel: \n");
		on_error();
	}
	status = pthread_join(thread, NULL);
	if(status) {
		fprintf(stdout, "main(): pthread_join: \n");
		on_error();
	}
	fprintf(stdout, "main(): CANCEL SUCCESS\n");
	return EXIT_SUCCESS;
}
