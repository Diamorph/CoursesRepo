#include <stdio.h>
#include <math.h>

int main(){
int result, num, num1;
num = 7;
num = num % 7;

switch (num) {
case 1:{
    printf("середа",num);
	break;
}
case 2:{
    printf("четвер", num);
	break;
}
case 3:{
    printf("п'ятниця", num);
	break;
}
case 4:{
    printf("субота", num);
	break;
}
case 5:{
    printf("неділя", num);
	break;
}
case 6:{
    printf("понеділок", num);
	break;
}
case 0:{
    printf("вівторок", num);
	break; }
}
system("pause");
	return 0;

}