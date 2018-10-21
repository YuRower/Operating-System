#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> 
#include <unistd.h>
#include <string.h>


size_t buffer;
char * user_name;
char * command;
void help(char* name) {
	fprintf(stdout, "HELP\n");
	fprintf(stdout,"usage: %s\n\t-h(--help) help with environment option\n\t-b<int_var>(--buffer<int_var>) assing buffer size(default size 127)\n",name);
}
void wait_on_exit(void){
	fprintf(stderr, "EXIT from program was invoked...\n");
	fprintf(stderr, "Wait 3 seconds...\n");
	sleep(3);
	free(command);
	system("clear");
}
void init(void){
	user_name = getenv("USER");
	command = (char *) malloc(sizeof(char) * buffer);
	atexit(wait_on_exit);
}

void parsearg(int argc, char ** argv){
	int c;
	const struct option long_opt[] = {
		{"help", 0, NULL, 'h'},
		{"buffer",1, NULL, 'b'},
		{NULL, 0, NULL, 0}
	};
	buffer = 127;
	while (1) {
			if ((c = getopt_long(argc, argv, "h:b:", long_opt, NULL)) == -1)
				break;
		switch(c){
			case 'h':
				fprintf(stdout,"Option %c selected \n",(char) c);
			    help(argv[0]);
				//exit(EXIT_SUCCESS);
				break;
			case 'b':
				fprintf(stdout,"Option %c selected \n",(char) c);
				buffer = atoi(optarg);
				break;
			case '?':
				fprintf(stderr, "%s\n", "Unknown option");
				break;
			default:
				break;
		}
	}
}

int main(int argc, char ** argv)
{
	parsearg(argc, argv);
	init();
	system("clear");
	printf("Hello, %s!\n", user_name);
	do{
		fprintf(stdout,"User = [%s]\nInput some command =", user_name);
		fscanf(stdin,"%[^\n]%*c", command);
		if (!strcmp(command, "stop")){//return 0 when match
			printf("break\n");
			break;
		}
		int status = system(command);
		if(status != EXIT_SUCCESS){
			fprintf(stderr, "command = %s \nexit code = %d\n", command, status);
			exit(EXIT_FAILURE);
		}
	}while(1);
	return EXIT_SUCCESS;
}
