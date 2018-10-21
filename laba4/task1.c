#include <stdlib.h>
#include <stdio.h>

int main (void) 
{
	fprintf (stderr, "Start the program\n");
 	system("dir");
 	system("sleep 2");
	system("env");
	system("sleep 2");
	system("uname");
	system("sleep 2");
	system("ps ax");
	system("sleep 2");
	fprintf (stderr, "Stop the program\n");
	return EXIT_SUCCESS;
}
