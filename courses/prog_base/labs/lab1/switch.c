
#import <math.h>

int exec(int op, int a, int b) {
   int result, n0 = 7, n1 = 1;

	switch (op) {
	case 0: {
				result = -a;
				break;
	}
	case 1:{
			   result = a + b;
			   break;
	}
	case 2:{
			   result = a - b;
			   break;
	}
	case 3:{
			   result = a * b;
			   break;
	}
	case 4:{
			   result = a / b;
			   break;
	}
	case 5:{
			   result = abs(a);
			   break;
	}
	case 6:{
			   result = pow(a, b);
			   break;
	}
	case 7:{
			   result = a % b;
			   break;
	}
	case 13:{
				result = a % b;
				break;
	}
	case 77:{
				result = a % b;
				break;

	}
	case 8: {
	    int max;
	    if (a > b) {
            max = a;
	    } else {
	     max = b;
	    }
				result = max;
				break;
	}
	case 9: {
	    int min;
	    if (a > b) {
             min = b;
	    } else {
	    min = a;
	    }
				result = min;
				break;
	}
	case 10: {
				 result = abs(a) * (abs(b) % 8);
				 break;
	}
	case 11: {
				 const double PI = 3.14159265;
				 result = (n0 + 1)*PI*cos((n1 + 1)* a* b) / a;
				 result = floor(result + 0.5);
					 break;
	}
	default: {
				 if (op < 100) {
					 result = (op % abs(a + 1)) + (op % abs(b + 1));
				 }
				 if (op > 100) {
					 result = -1;
				 }
				 break;
	}
	}

   return result;
}
