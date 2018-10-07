#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "functs.h"

char *value;
char *assigned;

void help(char* name) {
	fprintf(stdout, "HELP\n");
	fprintf(stdout,"usage: %s\n\t-h(--help) help with environment option\n\t-i<var>(--info<var>) get info about specified env_var\n\t-s<var>=<value>(--set <var>=<value>) set specified env_var value\n\t-a<var>-v<value>(--assign<var>--value<value>) set specified env_var value otherwise set empty line\n\t-d<var>(--del<var>) delete specified env_var\n\t-c(--clear)completely clean the environment.\n\t", name);
}
void infovar(const char * name) {
	char * env_var = getenv(name);
	fprintf(stdout, "Value =%s \n", env_var);
	if (env_var)
		fprintf(stdout, "Info about environment var %s=%s\n", name, env_var);
	else
		fprintf(stderr, "Specified var \"%s\" not found\n", name);
}

int set_env_var(char * name, char * value) {
	fprintf(stdout, "Environ var: %s value is %s\n", name, value);
	int overwrite=1;
	return setenv(name, value, overwrite);
}

void setvar(char * arg) {
	if (arg) {
		char * name = strtok(arg, "=");
		char * value = strtok(NULL, "=");
		//printf("Result: %s , %s \n", name, value);
		fprintf(stdout, "Name = %s,value = %s\n", name, value);
		int result = set_env_var(name, value);
		if (result){
			printf("Error occured:(not enough memory)");
		}else{
			fprintf(stdout, "Seted var: %s,", name);
			infovar(name);
		}
	}

}

void set_a(char * pa){
	fprintf(stdout, "Set : %s\n", pa);
	assigned = pa;
}

void set_v(char * pv){
	fprintf(stdout, "Set : %s\n", pv);
	value = pv;
}

void assign_value(){
	if (assigned && value)
		set_env_var(assigned, value);
	else if (assigned && !value)
		set_env_var(assigned, "");
	else if (value)
		fprintf(stderr, "not found assigned value\n");
}

int deletevar(const char * name){
	//fprintf(stdout, "GETENV: %s=%s\n", name, getenv(name));
	infovar(name);
	int res = unsetenv(name);
	fprintf(stdout, "Result: %d", res);
	if (res)
		fprintf(stderr, "VAR %s not found \n", name);
	else
		fprintf(stdout, "var %s deleted \n", name);
	return res;
}

int clearenvr(void){
	return clearenv();
}
void usage(char *name){
     fprintf(stdout,"%s\n",name );
	return;
}
