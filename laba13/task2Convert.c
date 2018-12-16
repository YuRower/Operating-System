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
	const char *name[2];
	name[0] = "aaa.fifo";
	name[1] = "bbb.fifo";
	int w, r;
	char* str = malloc(BUFF * sizeof(char));

	mkfifo(name[0], 0666);
	mkfifo(name[1], 0666);
	
	r = open(name[0], O_RDONLY );
	if(r<0){
		printf("Can\'t open FIFO for reading\n");
		exit(-1);
	}
	w = open(name[1], O_WRONLY );
	if(w<0){
		printf("Can\'t open FIFO for writing\n");
		exit(-1);
	}
	while(1) {
		read(r, str, BUFF);	
		if(!strcmp(str, "stop\n")) break;
		int len = strlen(str);
		for(int i = 0; i < len; i++)
			if(isalpha(str[i]))
				str[i] = toupper(str[i]);
		write(w, str, BUFF);
}

	free(str);
	close(w);
	close(r);	

	return EXIT_SUCCESS;
}
