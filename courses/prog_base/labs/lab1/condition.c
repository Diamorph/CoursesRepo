
#import <math.h>

int satisfies(int a, int b, int c) {
   int n0 = 7, n1 = 1, result = 0, min0, max0;
   if (a < 0 && b < 0 && c < 0) {          // �� ����� ��'���
		int sum2;
		if (a < b){
			min0 = a;
		}
		else {
			min0 = b;
			if (min0 > c)    {
				min0 = c;
			}
		}                               // ������ ���������� � ��� �����
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
		if (modmin1 = 1 && modmin < 256 && sum2 < -256) {  //���� sum2 ����� -256, � modmin � �������� ����� � modmin ����� 256 ��:
			result = 1;                                   //��������� ���� True
		}
    if (abs(sum2) - modmin < 16 || abs(sum2) < 16) {   // ���������: True ���� ������ ������ sum2 � modmin ����� 16
				result = 1;                                 //��� ������ sum2 ����� 16;
			}
}
	if (a >= 0 && b < 0 && c < 0) {                                                  //���� ��� �䒺���� ����� ��:
		int sum = (b + c)*(n0 + n1);                                                //��������� - �� ���� ��� ���� �䒺���� �����
		if (sum > -256){                                                         //��������� �� ���� n0 i n1 ����� �� -256;
			result = 1;
		}
    }
	if (b >= 0 && a < 0 && c < 0) {                                                  //���� ��� �䒺���� ����� ��:
		int sum = (a + c)*(n0 + n1);                                                //��������� - �� ���� ��� ���� �䒺���� �����
		if (sum > -256){                                                         //��������� �� ���� n0 i n1 ����� �� -256;
			result = 1;
		}
	}
		if (c >= 0 && b < 0 && a < 0) {                                                  //���� ��� �䒺���� ����� ��:
			int sum = (a + b)*(n0 + n1);                                                //��������� - �� ���� ��� ���� �䒺���� �����
			if (sum > -256){                                                         //��������� �� ���� n0 i n1 ����� �� -256;
				result = 1;
			}
        }
		if (a >= 0 && b >= 0 && c < 0 && c > -256) {                                         //���� ����� ���� � ��� �䒺��� ��:
			result = 1;
		}                                                             //��������� - �� �� �䒺��� ����� ����� -256;
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

