
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#define MATRIXDIMENSION 26

char matrix[26][26];
char encrypted[10000];
void populateMatrix() {
	int i, j;

	int letter = (int)'A';
	for (i = 0; i < MATRIXDIMENSION; i++) {
		for (j = 0; j < MATRIXDIMENSION; j++) {
			if ((int)letter + i + j > 90)
			{
				matrix[i][j] = (char)(letter + i + j- 26);
			}
			else {
				matrix[i][j] = (char)(letter + i + j);
			}
		}
	}
}

void encryptText(char key[], char plainText[]) {
	int i, j;

	for (i = 0; i < strlen(plainText); i++) {
		int line = (int)plainText[i]-65;
		int column = (int)key[i % strlen(key)] - 65;
		encrypted[i] = matrix[line][column];
	}
}

int main()
{
	FILE *f, *g;
	char plainText[1000];
	char key[1000];
	int ret, i, j;
	fopen_s(&f, "key.txt", "rt");
	fopen_s(&g, "plain.txt", "rt");
	while (fgets(plainText, 1000, g) != NULL && fgets(key, 1000, f) != NULL) {
		populateMatrix();
		for (i = 0; i < MATRIXDIMENSION; i++) {
			for (j = 0; j < MATRIXDIMENSION; j++) {
				printf("%c ", matrix[i][j]);
			}
			printf("\n");
		}

		encryptText(key, plainText);
		for (i = 0; i < strlen(encrypted); i++) {
			printf("%c", encrypted[i]);
		}
	}

	fclose(f);
	scanf_s("%d", &ret);
	return 0;
}


