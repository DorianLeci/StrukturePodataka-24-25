#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define ERROR_OPENING_FILE -1
#define BUFFER_SIZE 1024


typedef struct {
	char ime_ime[50];

}student;
int count_rows(char *fileName);

int main() {
	printf("\nHello world!!\n");
	char tekst[10];

	

	int uspjesno = OpenFile();

	return 0;
}
int count_rows(char *fileName) {
	FILE *file = NULL;
	int brojac = 0;
	char buffer[BUFFER_SIZE];


	file = fopen(fileName, "r");

	if (file == NULL) {
		return ERROR_OPENING_FILE;
	}

	while (!feof(file)) {
		fgets(buffer, BUFFER_SIZE, file);
			brojac++;
	}
	
	rewind(file);

	fclose(file);
}