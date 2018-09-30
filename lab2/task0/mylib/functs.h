#ifndef _POINTS_H_

#define _POINTS_H_
extern int  MAX_POINT;
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
}points[20];

struct Point curr_point;
struct Point closest_point;
struct Point new_point;

struct Point gen_point(double , double , char );
int len();
double distance(struct Point *, struct Point *);
struct Point  find_min_weigth ();
struct Point find_closest_point (struct Point *);
void print_distance (struct Point );
struct Point sum_up_points(struct Point *, struct Point *);
void change_weight( struct Point *);

#endif 
