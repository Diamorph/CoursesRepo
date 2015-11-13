#include <math.h>

double calc (int n, int m)
{

double res = 0, res1 = 0, res2 = 0;
    int n1 = 1;
    int i,j;
    for( i = 1; i <= n; i++){
        res1 = sin((2 * M_PI) / i) + res1;
            for  (j = 1; j <= m; j++){
                res2 = pow( j, n1 + i) + res2;
        }
        res2 = sqrt(res2);
        res = (res1 * res2) + res;
    }
return res;
}
