#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h> 
#include "funct.h"
void delay(int number_of_seconds) { 
    int milli_seconds = 1000 * number_of_seconds; 
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds) ; 
} 
char gen_bandit(){
			switch(rand() % 3){
				case 0:
					return 'O';
				case 1:
					return 'P';
				case 2:
					return 'X';		
			}
		}
	

void print_bandit(char array[3][3]){		
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			for (int i = 0; i < 250; ++i){
			delay(1);
			array[x][y] = gen_bandit();
			printf("[%c]", array[x][y]);
			printf("\r");
			fflush(stdout);
		}
					printf("\n");
		}
					printf("\n");
	}

}

void print_final_result( char array[3][3] ){
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			printf("[%c] ", array[x][y]);
		}
				printf("\n");
	}
				printf("\n");
}

	
int countWins(int type, char array[3][3]){
	int wins = 0;
	switch(type){
		case 0: 
			for(int x = 0; x < 3; x++){
				if(array[x][0] == array[x][1] && array[x][1] == array[x][2]){
					wins++;
				}
			}
			break;
		case 1: 
			for(int x = 0; x < 3; x++){
				if(array[0][x] == array[1][x] && array[1][x] == array[2][x]){
					wins++;
				}
			}
			break;
		case 2: 
			if(array[0][0] == array[1][1] && array[1][1] == array[2][2]){
				wins++;
			}
			
			if(array[0][2] == array[1][1] && array[1][1] == array[2][0]){
				wins++;
			}
			break;
	}
	return wins;
}

