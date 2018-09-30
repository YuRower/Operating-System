#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "mylib/functs.h"



int main(){
    //__time_t t;
    //srand((unsigned) time(&t));
    printf("Enter number of points: ");
    scanf("%d", &MAX_POINT);
    printf("%d\n", MAX_POINT);

    char c = 'A';
    for (int i = 0; i < MAX_POINT; ++i){
        points[i]= gen_point(0.0,10.0, c++);
    }

for (int i = 0; 0 < MAX_POINT-1; ++i){
    curr_point =  find_min_weigth();
    print_distance(curr_point);
    closest_point= find_closest_point(&curr_point);
    new_point = sum_up_points(&curr_point,&closest_point);
    change_weight(&new_point);    
}

    printf(" Points that remain %d\n", MAX_POINT);

printf("The name of point that has stayed %c , weight = %d \n",new_point.name.name_point,new_point.weight);
        return 0;
 }
