#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int BUFF_SIZE;
int shm_id;

char *append(const char *s, char c){
    int len = strlen(s);
    char buf[len+2];
    strcpy(buf, s);
    buf[len] = c;
    buf[len + 1] = '\0';
    return strdup(buf);
}
void sg_handler(int signo){printf("RECEIVE SIGNAL\n");}
int main(int argc, char const *argv[]){

	if(signal(SIGUSR2, sg_handler) == SIG_ERR){
		fprintf(stderr, "\ncan't catch SIGUSR1\n");
		exit(EXIT_FAILURE);
	}

	char *shm_adr;
	bool flag = true;

	if(argc < 3){
		flag = false;
	}

	 if(flag){
		shm_id = atoi(argv[1]);
		BUFF_SIZE = atoi(argv[2]);
	}

	shm_adr = (char *) shmat(shm_id, NULL, 0);
	if (shm_adr == (char *) -1) {
		fprintf(stderr, "shmat() error\n");
		return EXIT_FAILURE;
	}
    
	char *tmp = malloc(256 * sizeof(char));
	while(1){
		fprintf(stdout, "Enter a number \n");
		int len = 0;
		for(int i = 0; i < BUFF_SIZE; i++){
			gets(tmp);
			if(!strcmp(tmp, "stop")){
				fprintf(stdout, "STOP! \n");
				kill(getppid(), SIGUSR1);
				return EXIT_SUCCESS;
			}
			printf("You entered =====> %s\n",  tmp);
			tmp = append(tmp, '&');
			len += sprintf(shm_adr+len, tmp);//Возвращаемая величина равна количеству символов, действительно занесенных в массив.
		}
		fprintf(stdout, "Finish, send signal for calculating... \n");
		kill(getppid(), SIGUSR2);
		pause();
	}
	return EXIT_SUCCESS;
}
