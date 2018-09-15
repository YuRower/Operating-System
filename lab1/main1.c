#include <stdio.h>
#include "functs.h"

int main (void ){
	double res;
	res = get_x();
	printf("%lf\n", f(res));
	printf("%lf\n", g(res));

return 0;
}