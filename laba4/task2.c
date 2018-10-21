#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
char * p_str;
char * token;
p_str = (char *) malloc(sizeof(char) * 256);
if(p_str != NULL){
	scanf("%20[^\n]", p_str);
	printf("%s\n", p_str );
	token = strtok(p_str, ";");
	while( token != NULL ) {
     	printf("%s\n", token );
     	system(token); 
      	token = strtok(NULL, ";");
	}
}else{
 	printf("Не удалось выделить память.");
}
free(p_str);
//return 0;
exit(0);
} 