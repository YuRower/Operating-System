#include <stdio.h>
#include <math.h>

int get_x () {
	double  x ;
	scanf("%lf",&x);
	printf("%lf",x);
	return x;
}
double f (double x ){
	return exp(-fabs(x))*sin(x);
}
double g (double x ){
		return exp(-fabs(x))*cos(x);

}
int main (void ){
	double res;
	res = get_x();
	printf("%f\n", f(res));
	printf("%f\n", g(res));

return 0;
}