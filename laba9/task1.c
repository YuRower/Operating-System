#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h> 
#include <getopt.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define size 10
int on_error(char * err_info){ 
  fprintf(stderr, "%s Error\n" , err_info); 
  return EXIT_FAILURE;    
}


int thread_count = 8, sleeping_time = 1;
int ptr_value;
sem_t  is_empty_items ,is_full_items;
int buff[size];
pthread_t *threads = NULL;
pthread_mutex_t lock;

int get_rand_range_int(int dMin, int dMax){
	srand(time(NULL)+pthread_self());
	return (rand() % (dMax + 1 - dMin)) + dMin;
}

void destroy(void){
	printf("destroy\n");
	free(threads);
	pthread_mutex_destroy(&lock);
	sem_destroy(&is_empty_items);
	sem_destroy(&is_full_items);
}

void init(void){
	printf("init\n");
	int s;
	int m;
	m = pthread_mutex_init(&lock, NULL);// для критической секции
	if(m) on_error("init(): sem_init lock");

	s = sem_init(&is_empty_items, 0, size);//семафор может быть совместно использован разными процессами.
	if(s) on_error( "init(): sem_init empty");	

	s = sem_init(&is_full_items, 0, 0);
	if(s) on_error("init(): sem_init full");//если 0 — буфер пуст

	threads = (pthread_t*) malloc(sizeof(pthread_t) * thread_count);

	if(threads == NULL)
		exit(EXIT_FAILURE);
}

void add_to_buff(int rand){
	sem_getvalue(&is_full_items, &ptr_value);
	buff[ptr_value] = rand;
}

int get_last(void){
	sem_getvalue(&is_full_items, &ptr_value);
	return buff[ptr_value];
}

void * thread_producer(void * arg){
	int old_cancel_state;
	while(1){
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
		int r = get_rand_range_int(1, 100);
		sem_wait(&is_empty_items);
		pthread_mutex_lock(&lock);
		add_to_buff(r);
		pthread_mutex_unlock(&lock);
		sem_post(&is_full_items);
		fprintf(stdout, "thread_producer id: %lu\tproducer: %d\tsize: %d\n", pthread_self(), r, ptr_value);
		pthread_setcancelstate(old_cancel_state, NULL);
	}
	return NULL;
}

void * therad_consumer(void * arg){
	int old_cancel_state;
	while(1){
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
		int r;
		sem_wait(&is_full_items);
		pthread_mutex_lock(&lock);
		r = get_last();
		pthread_mutex_unlock(&lock);
		sem_post(&is_empty_items);
		fprintf(stdout, "thread_consumer id: %lu\tconsumer: %d\tsize: %d\n", pthread_self(), r, ptr_value);
		pthread_setcancelstate(old_cancel_state, NULL);
	}
	return NULL;
}


void parsearg(int argc, char ** argv){
	int res, ind;
	const struct option long_opt[] = {
		{"help", 0, NULL, 'h'},
		{"thread",1, NULL, 't'},
		{"sleep", 1, NULL, 's'},
		{"size", 1, NULL, 'n'},

		{NULL, 0, NULL, 0}
	};	
	while((res = getopt_long(argc, argv, "ht:s:n:", long_opt, &ind)) != -1){
		switch(res){
			case 'h':
				fprintf(stdout, "-t | --therad [int]\tthread_count\n-s | --sleep [int]\tsleeping time\n");//-n | --size [int]\tsize of buff\n");
				exit(-1);
				break;
			case 't':
				thread_count = atoi(optarg);
				break;
			case 's':
				sleeping_time = atoi(optarg);
				break;
			/*case 'n':
				size = atoi(optarg);
				break;*/
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
	for(int i = 0; i < thread_count; i++){
		if((i & 1) || (i < 2))
			s = pthread_create(&threads[i], NULL, thread_producer, NULL);
		else
			s = pthread_create(&threads[i], NULL, therad_consumer, NULL);

		if(s) on_error( "main(): pthread_create");
	}

	sleep(sleeping_time);//через заданное время отменяем потоки

	for(int i = 0; i < thread_count; i++){
		s = pthread_cancel(threads[i]);
		if(s) on_error( "main(): pthread_cancel");
	}

printf("all thread were canceled\n");
    printf("exit\n");
	return EXIT_SUCCESS;
}