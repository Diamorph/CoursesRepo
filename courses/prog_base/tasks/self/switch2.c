#include <stdio.h>
#include <math.h>

int main(){
int result, num, num1;
num = 7;
num1 = num % 7;

switch (num1) {
case 1:{
    printf("������",num);
	break;
}
case 2:{
    printf("������", num);
	break;
}
case 3:{
    printf("�'������", num);
	break;
}
case 4:{
    printf("������", num);
	break;
}
case 5:{
    printf("�����", num);
	break;
}
case 6:{
    printf("��������", num);
	break;
}
case 0:{
    printf("�������", num);
	break; }
}
system("pause");
	return 0;

}
