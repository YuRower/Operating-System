#include <stdio.h>
#include <math.h>
#include "functs.h"
double f (double x ){
	printf("f func");
	return exp(-fabs(x))*sin(x);
}
double g (double x ){
	printf("g func");
		return exp(-fabs(x))*cos(x);

}

int get_x () {
	double  x ;
	scanf("%lf",&x);
	return x;
}


