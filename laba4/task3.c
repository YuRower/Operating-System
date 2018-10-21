#include <stdio.h>
#include <stdlib.h>

void callback1(void) { 
	system("sleep 1");
	printf("Callback1 invoked\n");
	 }
void callback2(void) {
	system("sleep 1");
 	printf("Callback2 invoked\n"); 
}
void callback3(void) { 
	system("sleep 1");
	printf("Callback3 invoked\n");
 }

int main(int argc, char **argv) 
{
	printf("Callback1 registration\n");
	if(atexit(callback1)) 
		fprintf(stderr, "Callback1 registration failed\n");
	printf("Callback2 registration\n");
	if(atexit(callback2)) 
		fprintf(stderr, "Callback2 registration failed\n");
	printf("Callback3 registration\n");
	if(atexit(callback3)) 
		fprintf(stderr, "Callback3 registration failed\n");
	return EXIT_SUCCESS; /* exit(0); */
}