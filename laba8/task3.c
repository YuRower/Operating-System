#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h> 
#include <getopt.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

int on_error(void){ 
  fprintf(stderr, "Error\n"); 
  return EXIT_FAILURE;    
}

int N = 10, thread_count = 5;
int *arr = NULL;
pthread_rwlock_t lock;
pthread_mutex_t mut;


int get_rand_range_int(const int min, const int max) {
	srand(time(NULL));
	pthread_mutex_lock(&mut);
   	int num = rand() % (max - min + 1) + min;
   	pthread_mutex_unlock(&mut);
    return num;
}
void * thread_detach_func(void * arg){
	while(1){
		int cnt = 0;
		fprintf(stdout, "THREAD DETACHED:\n");
		fprintf(stdout, "Contents of array :\n");
		for(int i = 0; i < N ; i++){
			fprintf(stdout, "%d ", arr[i]);
		}
		sleep(3);
	}
	return NULL;
}

void * thread_write(void * arg){
  while(1){
    int r = get_rand_range_int(0, N), pos = get_rand_range_int(0, N);
    pthread_rwlock_wrlock(&lock);
    arr[pos] = r;
    fprintf(stdout, "write: arr[%d] = %d\n", pos, r);
    pthread_rwlock_unlock(&lock);
    sleep(get_rand_range_int(1, 3));
  }
  return NULL;
}


void * thread_read(void * arg){
  while(1){
    int pos = get_rand_range_int(0, N);
    pthread_rwlock_rdlock(&lock);
    fprintf(stdout, "read: arr[%d] = %d\n", pos, arr[pos]);
    pthread_rwlock_unlock(&lock);
    sleep(get_rand_range_int(1, 3));
  }
  return NULL;
}
void parsearg(int argc, char ** argv){
  int res;
  const struct option long_opt[] = {
    {"help", 0, NULL, 'h'},
    {"pthread",1, NULL, 'p'},
    {"num", 1, NULL, 'n'},
    {NULL, 0, NULL, 0}
  };  
  while((res = getopt_long(argc, argv, "hp:n:", long_opt, NULL)) != -1){
    switch(res){
      case 'h':
        fprintf(stdout, "-p | --ptherad [int]\tthread_count\n-n | --num [int]\tarray size\n");
        exit(-1);
        break;
      case 'p':
        thread_count = atoi(optarg);
        break;
      case 'n':
        N = atoi(optarg);
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
  int m;
  parsearg(argc, argv);
  arr = (int *) malloc(N * sizeof(int));
  pthread_t *th_arr =(pthread_t *) malloc(thread_count * sizeof(pthread_t));
  s = pthread_rwlock_init(&lock, NULL);
  m = pthread_mutex_init(&mut, NULL);
	if(m) {
		on_error();
	}
  if(s) {on_error();}
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
    if((i & 1) || (i < 1))
      s = pthread_create(&th_arr[i], NULL, thread_write, NULL);
    else 
      s = pthread_create(&th_arr[i], NULL, thread_read, NULL);
    if(s) {on_error();}
  }

  for(int i = 0; i < thread_count; i++){
    s = pthread_join(th_arr[i], NULL);
    if(s) {
      on_error();
    }
  }
  free(arr);
  free(th_arr);
  pthread_rwlock_destroy(&lock);
  return EXIT_SUCCESS;
}