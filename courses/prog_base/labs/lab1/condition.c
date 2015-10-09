
#include <math.h>

int satisfies(int a, int b, int c) {
   int n0 = 7, n1 = 1, result = 0, min0, max0;
   if (a < 0 && b < 0 && c < 0) {          // всі числа від'ємні
		int sum2;
		if (a < b){
			min0 = a;
		}
		else {
			min0 = b;
			if (min0 > c)    {
				min0 = c;
			}
		}                               // модуль мінімального з цих чисел
		int modmin = abs(min0);
		if (min0 = a){                        // min = a
			sum2 = b + c;
		}
		if (min0 = b) {                      // min = b
			sum2 = a + c;
		}
		if (min0 = c) {                             // min = c
			sum2 = a + b;
		}
		int modmin1 = modmin;
		while (modmin1 >= 2) {
			modmin1 = (modmin1 / 2);
		}
		if (modmin1 = 1 && modmin < 256 && sum2 < -256) {  //Якщо sum2 менше -256, а modmin є степенню двійки і modmin менше 256 то:
			result = 1;                                   //Результат буде True
		}
    if (abs(sum2) - modmin < 16 || abs(sum2) < 16) {   // Результат: True якщо різниця модуля sum2 і modmin менша 16
				result = 1;                                 //або модуль sum2 менше 16;
			}
}
	if (a >= 0 && b < 0 && c < 0) {                                                  //Якщо два від’ємних числа то:
		int sum = (b + c)*(n0 + n1);                                                //Результат - це сума цих двох від’ємних чисел
		if (sum > -256){                                                         //помножена на суму n0 i n1 більша за -256;
			result = 1;
		}
    }
	if (b >= 0 && a < 0 && c < 0) {                                                  //Якщо два від’ємних числа то:
		int sum = (a + c)*(n0 + n1);                                                //Результат - це сума цих двох від’ємних чисел
		if (sum > -256){                                                         //помножена на суму n0 i n1 більша за -256;
			result = 1;
		}
	}
		if (c >= 0 && b < 0 && a < 0) {                                                  //Якщо два від’ємних числа то:
			int sum = (a + b)*(n0 + n1);                                                //Результат - це сума цих двох від’ємних чисел
			if (sum > -256){                                                         //помножена на суму n0 i n1 більша за -256;
				result = 1;
			}
        }
		if (a >= 0 && b >= 0 && c < 0 && c > -256) {                                         //Якщо тільки одне з них від’ємне то:
			result = 1;
		}                                                             //Результат - чи це від’ємне число більше -256;
        if (a >= 0 && c >= 0 && b < 0 && b > -256) {
			result = 1;
		}
        if (c >= 0 && b >= 0 && a < 0 && a > -256) {
			result = 1;
		}
        if (a >= 0 && b >= 0 && c >= 0){
			if (a < b){
				min0 = a;
			}
			else {
				min0 == b;
				if (min0 > c)    {
					min0 == c;
				}
			}
			if (a < b) {
				max0 == b;
			}
			else {
				max0 == a;
				if (max0 < c){
					max0 == c;
				}
			}
			int minmax = min0 * max0;
			if (minmax < 256){
				result = 1;
			}

		}
		return result;
	}

