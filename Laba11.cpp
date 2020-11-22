#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

const char* fname = "test.txt";
const char* result = "result.txt";
const int BUF_SIZE = 256;

void printFile(const char* file);

void ChangeCase(char* word);

int main() {
	setlocale(LC_ALL, "rus");
	FILE* in;
	FILE* out;
	char delim[]= " \t\n";
	if ((in = fopen(fname, "r"))==NULL) {
		printf("Ошибка открытия файла \"%s\"\n", fname);
		return 1;
	}
	out = fopen(result, "w");
	char buf[BUF_SIZE];
	int word_count = 0;
	while (fgets(buf,BUF_SIZE,in)!=NULL) {
		char* word;
		
		for (word = strtok(buf, delim); word != NULL; word = strtok(NULL, delim)) {
			unsigned char c;
			unsigned char first_symb=word[0];
			if ((++word_count % 2) == 0) {
				ChangeCase(word);			
				fprintf(out,"%s ", word);
			}
			else if (islower(first_symb)) {
				fprintf(out, "%s ", word);
			}
		}
		fprintf(out,"%c", '\n');
	}
	fclose(in);
	fclose(out);
	printFile(result);
	return 0;
}


void printFile(const char* file) {
	FILE* in;
	if ((in = fopen(file,"r")) == NULL) {
		printf("Ошибка открытия файла \"%s\"", file);
		return;
	}
	char str[256];
	while (fgets(str, 256, in) != NULL) {
		printf("%s", str);
	}
}

void ChangeCase(char* word) {
	char c;
	for (int i = 0; word[i]; i++) {
		c = word[i];
		if (isupper(c&0xFF))
			word[i] = tolower(c&0xFF);
		else
			word[i] = toupper(c&0xFF);

	}
}