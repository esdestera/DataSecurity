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
	int line;
	int column;
};

char alphabetMatrix[matrixDimension][matrixDimension];
char rightUpperCorner[matrixDimension][matrixDimension];
char leftBottomCorner[matrixDimension][matrixDimension];
Pair pairs[50];
int numOfPairs;
char encryptionResult[1000];
char decryptionResult[1000];

void GenerateAlphabetMatrix() {
	int i, j;
	
	char temp[100];
	int letter = (int)'A';
	for (i = 0; i < 25; i++)
	{	
		if (letter == 'J') {
			i--;
		}

		temp[i] = (char)letter;
		letter++;
	}

	for (i = 0; i < matrixDimension; i++) {
		for (j = 0; j < matrixDimension; j++) {
			alphabetMatrix[i][j] = temp[i * 5 + j];
		}
	}
}

void GenerateMatrixFormKey(char key[], char matrix[5][5])
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
		}
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

Pair RectangleRule(PositionInMatrix positionInFirstMatrix, PositionInMatrix positionInFourthMatrix, char matrix1[5][5], char matrix2[5][5]) {
	Pair result;

	result.first = matrix1[positionInFirstMatrix.line][positionInFourthMatrix.column];
	result.second = matrix2[positionInFourthMatrix.line][positionInFirstMatrix.column];

	return result;
}

PositionInMatrix GetPosition(char letter, char matrix[5][5]) 
{
	int i, j;
	PositionInMatrix position;
	for (i = 0; i < matrixDimension; i++) 
	{
		for (j = 0; j < matrixDimension; j++)
		{
			if (matrix[i][j] == letter) {
				position.line = i;
				position.column = j;
				return position;
			}
		}
	}	
}

void EncryptText(char plainText[]) 
{

	Pair result[50];
	int i;
	ReplaceLetter(plainText, 'J', 'I');
	PrepareText(plainText);

	for (i = 0; i < numOfPairs; i++) 
	{
		PositionInMatrix positionInFirstMatrix = GetPosition(pairs[i].first, alphabetMatrix);
		PositionInMatrix positionInFourthMatrix = GetPosition(pairs[i].second, alphabetMatrix);
				
		result[i] = RectangleRule(positionInFirstMatrix, positionInFourthMatrix, rightUpperCorner, leftBottomCorner);
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
		PositionInMatrix positionRightUpperCornerMatrix = GetPosition(pairs[i].first, rightUpperCorner);
		PositionInMatrix positionInLeftBottomCornerMatrix = GetPosition(pairs[i].second, leftBottomCorner);

		result[i] = RectangleRule(positionRightUpperCornerMatrix, positionInLeftBottomCornerMatrix, alphabetMatrix, alphabetMatrix);
	}

	for (i = 0; i < numOfPairs * 2; i += 2) {
		decryptionResult[i] = result[i / 2].first;
		decryptionResult[i + 1] = result[i / 2].second;
	}
}

int main()
{
	FILE *f, *g, *h, *f2;
	char key1[1000];
	char key2[1000];
	char plainText[1000];
	char encryptedText[1000];
	int ret, i, j;
	fopen_s(&f, "key.txt", "rt");
	fopen_s(&g, "plain.txt", "rt");
	fopen_s(&h, "encrypted.txt", "rt");
	fopen_s(&f2, "key2.txt", "rt");
	while (fgets(key1, 1000, f) != NULL && fgets(plainText, 1000, g) != NULL && fgets(encryptedText, 1000, h) != NULL && fgets(key2, 1000, f2) != NULL) 
	{
		GenerateAlphabetMatrix();
		
		GenerateMatrixFormKey(key1, rightUpperCorner);
		GenerateMatrixFormKey(key2, leftBottomCorner);
		for (i = 0; i < matrixDimension; i++) {
			for (j = 0; j < matrixDimension; j++) {
				printf("%c ", rightUpperCorner[i][j]);
			}
			printf("\n");
		}

		for (i = 0; i < matrixDimension; i++) {
			for (j = 0; j < matrixDimension; j++) {
				printf("%c ", leftBottomCorner[i][j]);
			}
			printf("\n");
		}

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

