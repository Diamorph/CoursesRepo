#include "nlp.h"

int main()
{
    char str[50000];

    FILE* fr = fopen("text.txt", "r");
	fread(str, sizeof(char), 50000, fr);

	text_t text = text_new(str);
	text_toSentences(text);

	FILE* fw = fopen("result.txt", "w");

	text_sortSentences(text);
	text_write(text, fw);


	text_free(text);

	fclose(fr);
	fclose(fw);

    return 0;
}
