#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <getopt.h>
#include <sys/wait.h>
#include <sys/types.h>

char * str = "Hello";
int time=3;

void parsearg(int argc, char ** argv){
	int res, ind;
	const struct option long_opt[] = {
		{"help", 0, NULL, 'h'},
		{"time", 1, NULL, 't'},
		{"string", 1, NULL, 's'},
		{NULL, 0, NULL, 0}
	};
	while((res = getopt_long(argc, argv, "ht:s:", long_opt, &ind)) != -1)
	{
		switch(res)
		{
			case 'h':
				printf("-t | --time [int] - seep time\n-s | --string [string] - string\n");
				exit(EXIT_FAILURE);
				break;
			case 't':
				time = atoi(optarg);
				break;
			case 's':
				str = optarg;
			case '?':
				fprintf(stderr, "%s\n", "Unknown option");
				break;
			default:
				break;
		}
	}
}

void sg_handler(int signo){
	printf("Sig alarm + %s\n",str);
	exit(1);
}
int main(int argc, char ** argv){
	parsearg(argc, argv);

	if(signal(SIGALRM, sg_handler) == SIG_ERR){
		fprintf(stderr, "\ncan't catch SIGALRM\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();

	if(!pid){
		alarm(time);
		pause();
		fprintf(stdout, "%s\n", str);
	}
	else
		return EXIT_SUCCESS;

	return EXIT_FAILURE;
}