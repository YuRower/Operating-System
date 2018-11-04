#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define time_count 3
int main(void) {
	pid_t pid;
	fprintf(stdout, "Пока всего один процесс\n");
	fprintf(stdout, "Вызов функции fork...\n");
	pid = fork();
	if (pid == 0){
		fprintf(stdout, "Процесс - потомок\n");
		int count = 0;
		time_t start = time(NULL);
		printf("Start %ld\n", start);
		while (time(NULL) - start < time_count)
			++count;
		time_t now = time(NULL);
		printf("Now %ld\n", now);
		fprintf(stdout,"Процесс - потомок, счетчик = %d\n", count);
	} else if (pid > 0) {
		fprintf(stdout, "Родительский процесс, pid потомка %d\n", pid);
		int count = 0;
		time_t start = time(NULL);
		printf("Start %ld\n", start);
		while (time(NULL) - start < time_count)
			++count;
		time_t now = time(NULL);
		printf("Now %ld\n", now);
		fprintf(stdout,"Родительский процесс, счетчик = %d\n", count);
	} else {
		fprintf(stderr,"Ошибка вызова fork, потомок не создан\n"); 
	}
	return 0;
}