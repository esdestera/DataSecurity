#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#define MATRIXDIMENSION 26

char matrix[26][26];
char encrypted[10000];
char text[10000];
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

void decryptText(char key[], char cypheredText[]) {
	int i, j;

	for (i = 0; i < strlen(cypheredText); i++) {
		int line = (int)key[i % strlen(key)] - 65;    //(int)key[i % strlen(key)] - aici iau numarul ascii pentru litera, stiind ca matricea contine pe linie albabetul trebuie sa merg pe linia corespunzatoare literei
		char element = cypheredText[i];
		for (j = 0; j < MATRIXDIMENSION; j++) {
			if (matrix[line][j] == element) {
				text[i] = (char)j + 65;					//am gasit coloana, luam litera care se afla la j + 65
			}
		}
	}
}

void removeSpaces(char str[])
{	
	int count = 0;
	int i;
	for (i = 0; str[i]; i++)
		if (str[i] != ' ') {
			str[count++] = str[i];
		}	

	str[count] = '\0';
}

int main()
{
	FILE *f, *g, *h;
	char plainText[1000];
	char cypheredText[1000];
	char key[1000];
	int ret, i, j;
	fopen_s(&f, "key.txt", "rt");
	fopen_s(&g, "plain.txt", "rt");
	fopen_s(&h, "decrypted.txt", "rt");
	while (fgets(plainText, 1000, g) != NULL && fgets(key, 1000, f) != NULL && fgets(cypheredText, 1000, h)) {
		populateMatrix();
		for (i = 0; i < MATRIXDIMENSION; i++) {
			for (j = 0; j < MATRIXDIMENSION; j++) {
				printf("%c ", matrix[i][j]);
			}
			printf("\n");
		}			

		removeSpaces(key);
		removeSpaces(plainText);
		encryptText(key, plainText);
		for (i = 0; i < strlen(encrypted); i++) {
			printf("%c", encrypted[i]);
		}

		printf("\n");

		removeSpaces(cypheredText);
		decryptText(key, cypheredText);
		for (i = 0; i < strlen(text); i++) {
			printf("%c", text[i]);
		}
	}

	fclose(f);
	scanf_s("%d", &ret);
	return 0;
}
