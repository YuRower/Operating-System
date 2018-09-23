#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
static int  MAX_POINT =  10;
typedef struct 
{
    //char *str;
    char name_point ;
}PtrType;

struct Point{
    PtrType name;
    double x;
    double y;
    int weight;
}points[10] ;
//typedef struct Point points[MAX_POINT];
 
    struct Point gen_point(double min, double max, char char_num) {
    struct Point p;
    p.name.name_point = char_num;
    double range = (max - min)+min; 
    double div = RAND_MAX / range;
    p.x = min + (rand() / div);
    p.y = min + (rand() / div);
    p.weight= (int )min + (rand() / div);
    printf("%f and %f points of  = %c + weight %d \n", p.x , p.y ,p.name.name_point, p.weight);
    return p ;
}
 
double distance(struct Point *point1, struct Point *point2){
     return sqrt(pow(point1->x - point2->x, 2)+pow(point1->y - point2->y, 2));
 }
struct Point  find_min_weigth (){
    double  min =DBL_MAX  ; //points[0].weight;
    int index;
    for (int i = 0; i < MAX_POINT; ++i){
    if (points[i].weight < min ){
        min = points[i].weight;
        index = i;
    }
}
    printf("point with min weight is %c point weight= %d\n", points[index].name.name_point ,points[index].weight );
return points[index];
}

struct Point find_closest_point (struct Point *point1){
    double  min_dist = distance(&points[0],&points[1]);
    int index=0;
    for (int i = 0; i < MAX_POINT; ++i){
        if (point1->name.name_point != points[i].name.name_point){
      double  curr_dist =distance(point1,&points[i]);
    if (curr_dist < min_dist ){
        min_dist = curr_dist;
        index = i ;

        }
    }
}
//printf("distance  to closest_point of %c beetwen %c is %f \n"
            //, point1->name.name_point  ,points[index].name.name_point ,  min_dist);
return points[index];
}

void print_distance (struct Point point_from){
    for (int i =0  ; i < MAX_POINT ; ++i){
   // printf("distance  %c and %c =   %f \n"
           // , point_from.name.name_point ,points[i].name.name_point  ,distance(&point_from,&points[i]));
 }
}
struct Point sum_up_points(struct Point *curr, struct Point *closest){
        int tmp;
        printf("%c  + %c \n", closest->name.name_point , curr->name.name_point) ;

        printf("%d  + %d \n", closest->weight , curr->weight) ;
        closest->weight += curr->weight;
        printf("current weight of points =============%d name = %c\n ",closest->weight,closest->name.name_point);

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

int main(){
    struct Point curr_point;
    struct Point closest_point;
    struct Point new_point;
    char c = 'A';
    for (int i = 0; i < MAX_POINT; ++i){
        points[i]= gen_point(0.0,10.0, c++);
    }

for (int i = 0; 0 < MAX_POINT; ++i){
    curr_point =  find_min_weigth();
    print_distance(curr_point);
    closest_point= find_closest_point(&curr_point);
    new_point = sum_up_points(&curr_point,&closest_point);
}
    printf(" len %d\n", MAX_POINT);

//printf("%c\n", new_point.name.name_point);
        return 0;
 }


/*for (int i =0  ; i < MAX_POINT ; ++i){
    for (int j = 0; j < MAX_POINT; ++j){
    if (i!=j){
        printf("distance  %c and %c =   %f \n"
            , points[i].name.name_point,points[j].name.name_point  ,distance(&points[i],&points[j]));

    }
    }*/
