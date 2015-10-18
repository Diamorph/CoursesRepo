#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//double long2double(long long);

//int main()
//{
//signed long long a;
//double b;
//scanf("%lli", &a);
//b = long2double(a);
//if (abs(b*100000000) < 1)
//printf("%0.325llf", b);
//else
//printf("%0.40llf", b);
//system("pause");
//return 0;
//}

double long2double(long long a)
{
short bit[64];
short i;
int m;
double d = 0;
if (a >= 0)
{
bit[63] = 0;
}
else
{
bit[63] = 1;

}
for (i = 0; i <= 62; i++)
{
if (a == 0)
bit[i] = 0;
else
if (a >= 0)
{
bit[i] = a % 2;
if (a % 2 == 1)
a = (a - 1) / 2;
else
    if (a == 0)
bit[i] = 0;
else
a = a / 2;
}
else
{

bit[i] = abs(a % 2); // розбиття числа на біти
if (a % 2 == -1)
a = (a - 1) / 2;
else
a = a / 2;
}
}
m = bit[52];         // мантиса
for (i = 53; i <= 62; i++)
{
m = bit[i] * powf(2, i - 52) + m;
}
for (i = 51; i >= 0; i--)
{
d = d + bit[i] * powf(2.0, i - 52);
}
if (m == 0 && d == 0)
if (bit[63] == 0)
{
return 0;
}
else
{
return -0.00;
}
if (m == 2047 && d != 0)
{
if (bit[63] == 0)
return NAN;
else
return -NAN;
}
if (m == 2047 && d == 0)
{
if (bit[63] == 0)
return INFINITY;
else
return -INFINITY;
}
if (m == 0)
{
return d*pow(2.0, -1022);
if (bit[63] == 0)
return d*pow(2.0, -1022);
else
return -d*pow(2.0, -1022);
}
else
if (m != 0)
{
m = m - 1023;
if (bit[63] == 0)
return (1.0 + d)*pow(2.0, m);
else
return -(1.0 + d)*pow(2.0, m);
}
}
