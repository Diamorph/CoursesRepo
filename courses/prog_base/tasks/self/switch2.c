#include <stdio.h>
#include <math.h>

int main(){
int result, num, num1;
num = 7;
num1 = num % 7;

switch (num1) {
case 1:{
    printf("середа",num);
	break;
}
case 2:{
    printf("четвер", num);
	break;
}
case 3:{
    printf("п'€тниц€", num);
	break;
}
case 4:{
    printf("субота", num);
	break;
}
case 5:{
    printf("нед≥л€", num);
	break;
}
case 6:{
    printf("понед≥лок", num);
	break;
}
case 0:{
    printf("в≥второк", num);
	break; }
}
system("pause");
	return 0;

}
