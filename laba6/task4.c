#include <time.h>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef unsigned long long ull;

 struct thread_arg{ 
	int size; 
	void * arr;
 }; 

long factorial(int n){
  if (n == 0)
    return 1;
  else
    return(n * factorial(n-1));
}

ull catalan(int n){
	return n ? factorial(2 * n)/(factorial(n+1)*factorial(n)) : 1;
}

/*ull catalan(int n){
	return n ? 2 * (2 * n - 1) * catalan(n - 1) / (1 + n) : 1;
}*/

int on_error(void){ 
	fprintf(stderr, "Error\n"); 
	return EXIT_FAILURE;		
}
int checkPrimeNumber(int n){
    int j, flag = 1;
    for(j=2; j <= n/2; ++j){
     	if (n%j == 0){
            flag =0;
            break;
        }
    }
    return flag;
}

void * thread_prime(void * arg) {
	struct thread_arg * args = ( struct thread_arg*)arg;
	int n = args->size, size = 0, start_num = 2;
	int * res = malloc(n * sizeof(int));
	while(size != n){
		int num = start_num++;
		bool flag = checkPrimeNumber(num);
		if(flag){
			res[size++] = num;
				fprintf(stderr, "Thread for calculate prime.num: %d\n", res[size - 1]);
		}
	}
	args->arr = res;
	return NULL;
}



void * thread_catalan(void * arg) {
	struct thread_arg * args = ( struct thread_arg*)arg;
	int n = args->size;
	ull *res_glob = malloc(n * sizeof(ull));
	for(int i = 0; i < n; i++){
		res_glob[i] = catalan(i);	
			printf("Thread for calculate catalan.num: %llu\n", res_glob[i]);
	}
	return NULL;
}

int main(void){
	int **arr1;
	ull **arr2;
	struct thread_arg args1 = {100, &arr1};
	struct thread_arg args2 = {20, &arr2};
	pthread_t th_prime, th_catalan;

	if(pthread_create(&th_prime, NULL, thread_prime, &args1)){
		on_error();
	}

	if(pthread_create(&th_catalan, NULL, thread_catalan, &args2)){
		on_error();
	}

	if(pthread_join(th_prime, NULL)){
		fprintf(stderr, "Join1 error\n");
		return 1;
	}

	if (pthread_join(th_catalan, NULL)){
		fprintf(stderr, "Join2 error\n");
		return 1;
	}
	fprintf(stderr, "Main Thread have finished.\n");
	return EXIT_SUCCESS;
}