#include "nlp.h"

struct word_s  {
	char* str;
};

word_t word_new (char* buf) {
	word_t self = malloc(sizeof(struct word_s));
	self->str = malloc((strlen(buf) + 1)*sizeof(char));
	strcpy(self->str, buf);
	return self;
}

void word_free (word_t self) {
	free(self->str);
	free(self);
}


struct sentence_s {
	char* str;
	int size;
	word_t words[MAX_WORDS];
};

sentence_t sentence_new (char* buf) {
	sentence_t self = malloc(sizeof(struct sentence_s));
	self->str = malloc((strlen(buf) + 1)*sizeof(char));
	strcpy(self->str, buf);
	self->size = 0;
	return self;
}

void sentence_free (sentence_t self) {
	free(self->str);
	for (int i = 0; i < self->size; i++){
		word_free(self->words[i]);
	}
	free(self);
}

void sentence_toWords (sentence_t self) {
	char* str = malloc((strlen(self->str) + 1)*sizeof(char));
	char* str1 = str;
	strcpy(str, self->str);
	char * wordBuf = strtok(str, " ");
	while (wordBuf != NULL){
		self->words[self->size] = word_new(wordBuf);
		if (!isalnum(abs(self->words[self->size]->str[strlen(self->words[self->size]->str) - 1]))){
			self->words[self->size]->str[strlen(self->words[self->size]->str) - 1] = '\0';
		}
		self->size++;
		wordBuf = strtok(NULL, " ");
	}
	free(str1);
}

int sentence_getFirstLetter (sentence_t self) {
    return self->words[0]->str[0];
}


struct text_s {
	char* str;
	int size;
	sentence_t sentences[MAX_SENTENCES];
};

text_t text_new(char* buf) {
	text_t self = malloc(sizeof(struct text_s));
	self->str = malloc((strlen(buf) + 1) * sizeof(char));
	self->size = 0;
	strcpy(self->str, buf);
	return self;
}

void text_free (text_t self) {
	free(self->str);
	for (int i = 0; i < self->size; i++){
		sentence_free(self->sentences[i]);
	}
	free(self);
}

void text_toSentences (text_t self) {
	char* str = malloc((strlen(self->str) + 1)*sizeof(char));
	char* str1 = str;
	strcpy(str, self->str);
	char* p = strpbrk(str, ".?!");
	while (p != NULL){
		char ch = p[0];
		str[p - str] = '\0';
		char sentence[500];
		sprintf(sentence, "%s%c", str, ch);
		printf("%s\n", sentence);
		self->sentences[self->size] = sentence_new(sentence);
		sentence_toWords(self->sentences[self->size++]);
		str += p - str + 1;
		while (!isalnum(abs(str[0]))) str++;
		p = strpbrk(p + 1, ".?!");
	}
	free(str1);
}


void text_swapSentences (text_t self, int index1, int index2) {
    sentence_t temp = self->sentences[index1];
    self->sentences[index1] = self->sentences[index2];
    self->sentences[index2] = temp;
}

void text_sortSentences (text_t self) {
    for (int i = 0; i < self->size - 1; i++) {
        for (int j = 0; j < self->size - 1 - i; j++) {
            if (sentence_getFirstLetter(self->sentences[j]) > sentence_getFirstLetter(self->sentences[j + 1]))
                text_swapSentences(self, j, j + 1);
        }
    }
}

char* text_getSentenceWithCommas (text_t self, int index) {
    char* str = malloc((strlen(self->sentences[index]->str) + 1)*sizeof(char));
    strcpy(str, self->sentences[index]->str);
    char* copy = str;
    char resStr[MAX_WORDS*MAX_WORD_LENGTH];
    char* res = resStr;
    for (int i = 0; i < self->size; i++)
        sprintf(res, "%s, ", self->sentences[index]->words[i]->str);
    sprintf(res, "\n");
    free(copy);
    return res;
}

void text_write(text_t self, FILE* fw) {
    for (int i = 0; i < self->size; i++) {
        for (int j = 0; j < self->sentences[i]->size; j++) {
            fprintf(fw, "%s, ", self->sentences[i]->words[j]->str);
        }
        fprintf(fw, "\n");
    }
}
