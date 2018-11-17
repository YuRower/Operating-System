#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h> 
#include <getopt.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/syscall.h>
int on_error(void){ 
	fprintf(stderr, "Error\n"); 
	return EXIT_FAILURE;		
}

int thread_count = 0;
static pthread_key_t key;
static pthread_once_t once = PTHREAD_ONCE_INIT; 

typedef struct {
	int a;
	int b;
	char * str;
} args_t;

typedef unsigned long ul;

static void once_creator(void){
	pthread_key_create(&key, NULL);
}

void print(int rand){
	char *str = (char *) pthread_getspecific(key);
	fprintf(stdout, "%s RAND: %d\n", str, rand);
}


int get_rand_range_int(const int min, const int max) {
	srand(time(NULL));
    return rand() % (max - min + 1) + min;
}

void * func(void * arg){
	args_t * args = (args_t*)arg;
	char str[256];
	pthread_once(&once, once_creator);
	sprintf(str, "ID: %lu STR: %s ", pthread_self(), args->str);
	pthread_setspecific(key, str);
	int cnt = get_rand_range_int(args->a, args->b);
	while(cnt--)
		print(get_rand_range_int(args->a, args->b));
	return NULL;
}
char * get_rand_str(size_t len){
	char * str = malloc(sizeof(char) * len + 1);
	char * al = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
	int al_le = strlen(al);
	if(len){
		str[len] = '\0';
		for(int i = 0; i < len; i++){
 			usleep(100000);
 			str[i] = al[get_rand_range_int(0, al_le - 1)];

}
	}
	return str;
}

args_t * gen_arg(int a, int b, char * str){
	args_t * res = malloc(sizeof(args_t));
	res->a = a;
	res->b = b;
	res->str = str;
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
				fprintf(stdout, "-n | --num [int]\tsleep sec\n");
				break;
			case 'n':
				thread_count  = atoi(optarg);
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
	pthread_t * arr = malloc(thread_count * sizeof(pthread_t));
	int status;
	for(int i = 0; i < thread_count; i++){
		status = pthread_create(&arr[i], NULL, &func, gen_arg(1, 10, get_rand_str(get_rand_range_int(1, 20))));
			if(status) {
			fprintf(stdout, "main(): pthread_create: \n");
			on_error();
			}
	}
	
	for(int i = 0; i < thread_count; i++){
		status = pthread_join(arr[i], NULL);
			if(status) {
			fprintf(stdout, "main(): pthread_join: \n");
			on_error();
			}
	}
	return 0;
	
}
