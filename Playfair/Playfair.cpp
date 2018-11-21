// Playfair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define matrixDimension 5
struct Pair {
	char first;
	char second;
};

struct PositionInMatrix {
	int firstLine;
	int firstColumn;
	int secondLine;
	int secondColumn;
};

char matrix[matrixDimension][matrixDimension];
Pair pairs[50];
int numOfPairs;
char encryptionResult[1000];
char decryptionResult[1000];

void GenerateMatrix(char key[])
{
	int i, j, k = 0;
	int compareResult = 0;
	char temp[matrixDimension * matrixDimension];
	temp[0] = key[0];
	k++;
	for (i = 1; i < strlen(key); i++) {
		compareResult = 0;
		for (j = 0; j < k; j++) {
			if (temp[j] == key[i%strlen(key)]) {
				compareResult = 1;
				break;
			}
		}

		if (compareResult == 0) {
			temp[k] = key[i%strlen(key)];
			k++;
		}
	}

	int letter = (int)'A';
	for (i = k; k < 25; i++)
	{
		compareResult = 0;		
		for (j = 0; j < k; j++) {
			if (temp[j] == (char)letter) {
				compareResult = 1;
				break;
			}
		}

		if (compareResult == 0 && letter != 'J') {
			temp[k] = (char)letter;
			k++;
		}

		letter++;
	}
	
	for (i = 0; i < matrixDimension; i++) {
		for (j = 0; j < matrixDimension; j++) {
			matrix[i][j] = temp[i*5 + j];
			printf("%c ", matrix[i][j]);
		}
		printf("\n");
	}
}

void RemoveSpaces(char str[])
{
	int count = 0;
	int i;
	for (i = 0; str[i]; i++)
	{
		if (str[i] != ' ')
		{
			str[count++] = str[i];
		}

	}
	str[count] = '\0';
}

void ReplaceLetter(char text[], char letterToReplace, char letterToReplaceWith) {
	int i;

	for (i = 0; i < strlen(text); i++) {
		if (text[i] == letterToReplace) {
			text[i] = letterToReplaceWith;
		}
	}
}

void Append(char* s, char c) {
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
}

void PrepareText(char text[1000]) 
{
	int i, j;
	if (strlen(text) % 2 != 0) 
	{
		Append(text, 'X');
	}

	j = 0;
	i = 0;
	while(i < strlen(text)) 
	{
		pairs[j].first = text[i];
		pairs[j].second = text[i + 1];

		if (pairs[j].first == pairs[j].second) 
		{
			pairs[j].second = 'X';
		}
		i += 2;
		j++;
	}

	numOfPairs = j;
}

Pair ColumnRule(int column, Pair pair, int encryptOrDecrypt) 
{
	Pair result;
	int line;

	for (line = 0; line < matrixDimension; line++) 
	{
		if (matrix[line][column] == pair.first) 
		{
			result.first = matrix[(line + encryptOrDecrypt) % matrixDimension][column];
		}

		if (matrix[line][column] == pair.second)
		{
			result.second = matrix[(line + encryptOrDecrypt) % matrixDimension][column];
		}
	}

	return result;
}

Pair LineRule(int line, Pair pair, int encryptOrDecrypt)
{
	Pair result;
	int column;

	for (column = 0; column < matrixDimension; column++)
	{
		if (matrix[line][column] == pair.first)
		{
			result.first = matrix[line][(column + encryptOrDecrypt) % matrixDimension];
		}

		if (matrix[line][column] == pair.second)
		{
			result.second = matrix[line][(column + encryptOrDecrypt) % matrixDimension];
		}
	}

	return result;
}

Pair RectangleRule(PositionInMatrix position, Pair pair) {
	Pair result;

	result.first = matrix[position.firstLine][position.secondColumn];
	result.second = matrix[position.secondLine][position.firstColumn];

	return result;
}

PositionInMatrix GetPosition(Pair pair) 
{
	int i, j;
	PositionInMatrix position;
	for (i = 0; i < matrixDimension; i++) 
	{
		for (j = 0; j < matrixDimension; j++)
		{
			if (matrix[i][j] == pair.first) {
				position.firstLine = i;
				position.firstColumn = j;
			}

			if (matrix[i][j] == pair.second) {
				position.secondLine = i;
				position.secondColumn = j;
			}
		}
	}

	return position;
}

void EncryptText(char plainText[]) 
{

	Pair result[50];
	int i;
	ReplaceLetter(plainText, 'J', 'I');
	PrepareText(plainText);

	for (i = 0; i < numOfPairs; i++) 
	{
		PositionInMatrix position = GetPosition(pairs[i]);

		if (position.firstLine == position.secondLine) {
			result[i] = LineRule(position.firstLine, pairs[i], 1);
		}
		else {
			if (position.firstColumn == position.secondColumn) {
				result[i] = ColumnRule(position.firstColumn, pairs[i], 1);
			}
			else{
				result[i] = RectangleRule(position, pairs[i]);
			}
		}
	}

	for (i = 0; i < numOfPairs * 2; i += 2) {
		encryptionResult[i] = result[i / 2].first;
		encryptionResult[i + 1] = result[i / 2].second;
	}
}

void DecryptText(char encryptedtext[])
{

	Pair result[50];
	int i;
	PrepareText(encryptedtext);

	for (i = 0; i < numOfPairs; i++)
	{
		PositionInMatrix position = GetPosition(pairs[i]);

		if (position.firstLine == position.secondLine) {
			result[i] = LineRule(position.firstLine, pairs[i], -1);
		}
		else {
			if (position.firstColumn == position.secondColumn) {
				result[i] = ColumnRule(position.firstColumn, pairs[i], -1);
			}
			else {
				result[i] = RectangleRule(position, pairs[i]);
			}
		}
	}

	for (i = 0; i < numOfPairs * 2; i += 2) {
		decryptionResult[i] = result[i / 2].first;
		decryptionResult[i + 1] = result[i / 2].second;
	}
}

int main()
{
	FILE *f, *g, *h;
	char key[1000];
	char plainText[1000];
	char encryptedText[1000];
	int ret, i, j;
	fopen_s(&f, "key.txt", "rt");
	fopen_s(&g, "plain.txt", "rt");
	fopen_s(&h, "encrypted.txt", "rt");
	while (fgets(key, 1000, f) != NULL && fgets(plainText, 1000, g) != NULL && fgets(encryptedText, 1000, h) != NULL) 
	{
		int num = strlen(key);
		GenerateMatrix(key);
		RemoveSpaces(plainText);		

		printf("Plain text: ");

		for (i = 0; i < strlen(plainText); i++) 
		{
			printf("%c", plainText[i]);
		}

		printf("\nEncrypted text: ");

		EncryptText(plainText);
		for (i = 0; i < strlen(encryptionResult); i++) 
		{
			printf("%c", encryptionResult[i]);
		}

		printf("\nDecrypted text: ");

		DecryptText(encryptedText);
		for (i = 0; i < strlen(decryptionResult); i++) 
		{
			printf("%c", decryptionResult[i]);
		}
	}

	fclose(f);
	scanf_s("%d", &ret);
	return 0;
}

