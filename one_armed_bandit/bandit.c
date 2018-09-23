#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include "myLib/funct.h"

int main(int argc, char const *argv[]){
	int choice;
do{
 printf("Menu\n\n");
 printf("1. Play\n");
 printf("2. Exit\n");
 scanf("%d",&choice);
 switch (choice){
	   case 1: 
	   	srand(time(0)); 
		char banditArray[3][3];
		print_bandit(banditArray);
		print_final_result(banditArray);

		int rows = countWins(0, banditArray);
		int columns = countWins(1, banditArray);
		int diagonals = countWins(2, banditArray);

		int wins = rows + columns + diagonals;

		if(wins > 0){

			printf("[One Armed Bandit] Rows: %d  wins.\n",rows );
			printf("[One Armed Bandit] Columns: %d  wins.\n",columns );
			printf("[One Armed Bandit] Diagonals: %d  wins.\n",diagonals );
			printf("[One Armed Bandit] Won: %d  wins.\n",wins );
		}
		else {
			printf("[One Armed Bandit] No rows, columns or diagonal wins." );
		}
		break;
	case 2:
		printf("Goodbye\n"); 
        break;
 default: 
 		printf("Wrong Choice. Enter again\n");
        break;
}
}while (choice != 2);
		return 0;
}