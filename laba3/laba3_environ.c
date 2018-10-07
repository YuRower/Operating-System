#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "functs.h"
extern char ** environ;

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Info about environment\n"); 
		for (int i = 0; environ[i]; i++)
			fprintf(stdout, "%s\n", environ[i]);
	}else {
		int c;
		const struct option long_opt[] = {
			{"help", 0, NULL, 'h'},
			{"info", 1, NULL, 'i'},
			{"set", 1, NULL, 's'},
			{"assign", 1, NULL, 'a'},
			{"value", 1, NULL, 'v'},
			{"del", 1, NULL, 'd'},
			{"clear", 0, NULL, 'c'},
			{NULL, 0, NULL, 0}
		};
		while (1) {
			if ((c = getopt_long(argc, argv, "c:h:i:s:a:v:d:c:", long_opt, NULL)) == -1)
				break;
			switch (c) {
			case 'h':
				fprintf(stdout,"Option %c selected \n",(char) c);
				help(argv[0]);
				break;
			case 'i':
				fprintf(stdout,"Option %c selected \n",(char) c);
				infovar(optarg);
				break;
			case 's':
				fprintf(stdout,"Option %c selected \n",(char) c);
				setvar(optarg);
				break;
			case 'a':
				fprintf(stdout,"Option %c selected \n",(char) c);
				set_a(optarg);
				break;
			case 'v':
				fprintf(stdout,"Option %c selected \n",(char) c);
				set_v(optarg);
				break;
			case 'd':
				fprintf(stdout,"Option %c selected \n",(char) c);
				deletevar(optarg);
				break;
			case 'c':
				fprintf(stdout,"Option %c selected \n",(char) c);
				clearenvr();
				break;
			case '?':
				fprintf(stderr, "%s\n", "Unknown option");
				break;
			default:
				usage(argv[0]);
				return(-1);
			}
		}
		assign_value();
	}
	return(0);
}
