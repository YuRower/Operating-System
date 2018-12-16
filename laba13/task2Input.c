#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFF 256

int main(int argc, char *argv[]) {
	int w, r;
	const char *name[2];
	name[0] = "aaa.fifo";
	name[1] = "bbb.fifo";
	char* str = malloc(BUFF * sizeof(char));

	w = open(name[0], O_WRONLY);
	r = open(name[1], O_RDONLY);

	while(1) {
		fprintf(stdout, "INPUT STRING: ");
		fgets(str, BUFF, stdin);
		write(w, str, BUFF);
		if(!strcmp(str, "stop\n")) break;
		read(r, str, BUFF);
		printf("RETUENED STRING: %s\n", str);
	}

	free(str);
	close(w);
	close(r);

	return EXIT_SUCCESS;
}