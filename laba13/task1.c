#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define BUFF 256

char* str;
char* up_str;

void handler(int signo) {
	if(signo == SIGUSR2)
		exit(EXIT_SUCCESS);
}

void init(void){
	up_str = malloc(BUFF * sizeof(char));
	str = malloc(BUFF * sizeof(char));

}

void destpoy(void){
	free(up_str);
	free(str);
}

int main(void) {
	init();
	atexit(destpoy);
	int fd[2]; 
	pid_t pid;
	size_t size, len;

	if(signal(SIGUSR1, handler) == SIG_ERR) {
		fprintf(stderr, "\ncan't catch SIGALRM\n");
		exit(-1);
	}
	if(signal(SIGUSR2, handler) == SIG_ERR) {
		fprintf(stderr, "\ncan't catch SIGALRM\n");
		exit(-1);
	}
	if(pipe(fd) < 0) {
		fprintf(stderr, "Can\'t create pipe\n");
		exit(-1);
	}

	pid = fork();

	if(pid) {
		while(1) {
			fprintf(stdout, "INPUT STRING: ");
			fgets(str, BUFF, stdin);
			if(!strcmp(str,"stop\n")) {
				kill(pid,SIGUSR2);
					if(close(fd[0]) < 0){
						printf("Can\'t close input stream\n");
					}
					if(close(fd[1]) < 0){
						printf("Can\'t close output stream\n");
					}
				exit(EXIT_SUCCESS);
			}
			
			size = write(fd[1], str, BUFF);
			if(size != BUFF) {
				fprintf(stdout, "Can\'t write all string\n");
				exit(-1);
			}
			kill(pid, SIGUSR1);
			pause();
			size = read(fd[0], str, BUFF);
			if(size != BUFF) {
				fprintf(stdout, "Can\'t read all string\n");
				exit(-1);
			}
			fprintf(stdout, "RETURNED STRING: ");
			puts(str);
		}
	}else if(!pid) {
		while(1) {
			pause();
			size = read(fd[0], up_str, BUFF);
			if(size != BUFF) {
				fprintf(stdout, "Can\'t read all string\n");
				exit(-1);
			}
			len = strlen(up_str);
			for(int i = 0; i < len; i++)
				up_str[i] = toupper(up_str[i]);
			size = write(fd[1], up_str, BUFF);
			if(size != BUFF) {
				fprintf(stdout, "Can\'t write all string\n");
				exit(-1);
			}
			kill(getppid(), SIGUSR1);
		}
	} else {
		fprintf(stderr, "Can\'t create process\n");
		exit(-1);
	}
	return EXIT_SUCCESS;
}