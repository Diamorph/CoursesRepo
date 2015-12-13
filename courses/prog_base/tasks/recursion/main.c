#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int lastDigitCode(const char * pStart, const char * pChar) {
    if ((pStart > pChar) &&(!isxdigit(*pChar)))        return '0';// випадок 1, пуста строка або в строкі немає шістнадцяткової цифри
    else if (isxdigit(*pChar))   return (int)*pChar;  // випадок 2,  знайшли цифру
    else                        return lastDigitCode(pStart, pChar - 1); // правило
}

int main(){
	char str[100];
	gets(str);
	printf("result is  %c\n ", lastDigitCode(str, str + strlen(str) - 1));
	getchar();
	return EXIT_SUCCESS;
}
