#include <stdio.h>
#include <math.h>
#include "functs.h"
double f (double x ){
	return exp(-fabs(x))*sin(x);
}
double g (double x ){
		return exp(-fabs(x))*cos(x);

}

int get_x () {
	double  x ;
	scanf("%lf",&x);
	printf("%lf",x);
	return x;
}


