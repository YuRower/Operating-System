#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h> 
#include <getopt.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int on_error(char * err_info){ 
  fprintf(stderr, "%s Error\n" , err_info); 
  return EXIT_FAILURE;    
}


int thread_count = 8, period = 2, sleeping_time = 3;
int glob_var;
pthread_t *threads = NULL;
pthread_cond_t cond;
pthread_mutex_t mutex;


int get_rand_range_int(int dMin, int dMax){
	srand(time(NULL)+pthread_self());
	return (rand() % (dMax + 1 - dMin)) + dMin;
}
void destroy(void){
	printf("destroy\n");
	free(threads);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
}

void init(void)
{
	int s;

	s = pthread_cond_init(&cond, NULL);
	if(s) on_error( "init(): pthread_cond_init");

	s = pthread_mutex_init(&mutex, NULL);
	if(s) on_error("init(): pthread_mutex_init");

	threads = (pthread_t*) malloc(sizeof(pthread_t) * thread_count);

	if(threads == NULL)
		exit(EXIT_FAILURE);
}



void * thread_producer(void * arg){
	int old_cancel_state;
	while(1){
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
		pthread_mutex_lock(&mutex);
		glob_var = get_rand_range_int(1, 100);
		fprintf(stdout, "id: %lu write: %d\n", pthread_self(), glob_var);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
		sleep(period);
	}
	return NULL;
}

void * therad_consumer(void * arg){
	int old_cancel_state;
	while(1){
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
		fprintf(stdout, "id: %lu read: %d\n", pthread_self(), glob_var);
		pthread_mutex_unlock(&mutex);
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	}
	return NULL;
}



void parsearg(int argc, char ** argv){
	int res, ind;
	const struct option long_opt[] = {
		{"help", 0, NULL, 'h'},
		{"thread",1, NULL, 't'},
		{"period", 1, NULL, 'p'},
		{"sleep", 1, NULL, 's'},
		{NULL, 0, NULL, 0}
	};	
	while((res = getopt_long(argc, argv, "ht:p:s:", long_opt, &ind)) != -1)
	{
		switch(res)
		{
			case 'h':
				fprintf(stdout, "-t | --therad [int]\tthread_count\n-p | --period [int]\tperiod\n-s | --sleep [int]\tsleeping_time\n");
				exit(-1);
				break;
			case 't':
				thread_count = atoi(optarg);
				break;
			case 'p':
				period = atoi(optarg);
				break;
			case 's':
				sleeping_time = atoi(optarg);
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
	int s;
	parsearg(argc, argv);
	init();
	atexit(destroy);

	for(int i = 0; i < thread_count; i++)
	{
		if((i & 1) || (i < 2))
			s = pthread_create(&threads[i], NULL, therad_consumer, NULL);
		else
			s = pthread_create(&threads[i], NULL, thread_producer, NULL);

		if(s) on_error( "main(): pthread_create");
	}

	sleep(sleeping_time);

	for(int i = 0; i < thread_count; i++)
	{
		s = pthread_cancel(threads[i]);
		if(s) on_error( "main(): pthread_cancel");
	}
	printf("all thread were canceled\n");
    printf("exit\n");
	return EXIT_SUCCESS;
}