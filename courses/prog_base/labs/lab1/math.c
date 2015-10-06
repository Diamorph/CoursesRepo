#include <math.h>

double calc(double x, double y, double z) {
   double a, a0, a1, a2;
     int n0,n1;
        n0 = 7;
        n1 = 1;
    a0 = pow(x,y+1)/pow(x-y,1/z);
	a1 = y/((n0+1)*abs(x+y));
	a2 = sqrt(abs(cos(y)/sin(x)+n1));
	a = a0+a1+a2;
   return a;
}
