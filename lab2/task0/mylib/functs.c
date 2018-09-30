#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "functs.h"

int  MAX_POINT;
    struct Point gen_point(double min, double max, char char_num) {
    struct Point p;
    p.name.name_point = char_num;
    double range = (max - min)+min; 
    double div = RAND_MAX / range;
    p.x = min + (rand() / div);
    p.y = min + (rand() / div);
    p.weight= (int )min + (rand() / div);
    printf("Coordinates of point %c is  %f(x) and %f(y) , weight = %d \n",p.name.name_point, p.x , p.y , p.weight);
    return p ;
}
int len(){
    int length =  sizeof  points / sizeof  points[0];
    return length;
}
double distance(struct Point *point1, struct Point *point2){
     return sqrt(pow(point1->x - point2->x, 2)+pow(point1->y - point2->y, 2));
 }
struct Point  find_min_weigth (){
    double  min = DBL_MAX  ; //points[0].weight;
    int index;
    for (int i = 0; i < MAX_POINT; ++i){
    if (points[i].weight < min ){
        min = points[i].weight;
        index = i;
    }
}
    printf("Point with min weight is %c , weight= %d\n", points[index].name.name_point ,points[index].weight );
    return points[index];
}

struct Point find_closest_point (struct Point *start_point){
    double  min_dist = DBL_MAX ; //distance(&points[0],&points[1]);
    int index=0;
    for (int i = 0; i < MAX_POINT; ++i){
        if (start_point->name.name_point != points[i].name.name_point){
      double  curr_dist =distance(start_point,&points[i]);
    if (curr_dist < min_dist ){
        min_dist = curr_dist;
        index = i ;

        }
    }
}
printf("Distance to closest_point of beetwen %c  and  %c is %f \n", start_point->name.name_point  ,points[index].name.name_point ,  min_dist);
return points[index];
}

void print_distance (struct Point point_from){
    for (int i =0  ; i < MAX_POINT ; ++i){
            printf("%d\n", MAX_POINT);

    printf("distance  %c and %c =   %f \n" , point_from.name.name_point ,points[i].name.name_point  ,distance(&point_from,&points[i]));
 }
}
struct Point sum_up_points(struct Point *curr, struct Point *closest){
        printf("%d\n", MAX_POINT);

        int tmp;
        printf("%c  + %c = ", closest->name.name_point , curr->name.name_point) ;

        printf(" %d  + %d \n", closest->weight , curr->weight) ;
        closest->weight += curr->weight;
        printf("Current weight of point %c is %d\n ",closest->name.name_point,closest->weight);

        for (int i = 0; i < MAX_POINT; ++i){
                if (curr-> name.name_point == points[i].name.name_point) {
                    tmp =i;
                    break;
                }
            }
        for (int j=tmp ; j<MAX_POINT-1; j++){
                points[j] = points[j+1] ;
            }
           MAX_POINT = MAX_POINT-1;
    return *closest;
}

void change_weight( struct Point *point_to_change){
        printf("%d\n", MAX_POINT);

 for (int i = 0; i < MAX_POINT; ++i){
                if (point_to_change -> name.name_point == points[i].name.name_point) {
                     points[i].weight = point_to_change -> weight;
                    break;
                }
            }
}

