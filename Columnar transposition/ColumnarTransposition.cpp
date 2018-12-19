// ColumnarTransposition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>

char phaseIMatrix[1000][1000];
char phaseIIMatrix[1000][1000];
char encrypted[1000];

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

void phaseI(char key[], char plain[])
{
	int columns = strlen(key);
	int i, j, k;

	for (j = 0; j < columns; j++) 
	{
		phaseIMatrix[0][j] = key[j];
	}

	i = 1;
	while(i < strlen(plain))
	{
		for (j = 0; j < columns; j++)
		{
			if (((i - 1)* columns + j) < strlen(plain))
			{
				phaseIMatrix[i][j] = plain[(i - 1)* columns + j];
			}
			else
			{
				phaseIMatrix[i][j] = ' ';
			}
		}
		i++;
	}
}

void swap(char *xp, char *yp)
{
	char temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(char arr[], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray 
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array 
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element 
		swap(&arr[min_idx], &arr[i]);
	}
}

void phaseII(char key[], char plain[]) 
{
	int i, j;
	
	int lines = strlen(plain) / strlen(key);

	if (strlen(plain) % strlen(key) != 0) 
	{
		lines += 1;
	}

	selectionSort(key, strlen(key));
	int k = 0;

	while (k < strlen(key)) {
		for (j = 0; j < strlen(key); j++) 
		{
			if (phaseIMatrix[0][j] == key[k]) 
			{
				for (i = 0; i <= lines +1; i++) 
				{
					if (phaseIMatrix[i][j] == ' ') 
					{
						phaseIIMatrix[i][k] = ' ';
					}
					else 
					{
						phaseIIMatrix[i][k] = phaseIMatrix[i][j];
					}
				}
				k++;
			}
		}
	}

	for (i = 0; i < lines + 1; i++) {
		for (j = 0; j < strlen(key); j++) {
			printf("%c", phaseIIMatrix[i][j]);
		}
		printf("\n");
	}
}

void encryptText(char plain[], char key[]) {
	int i, j, k;
	phaseI(key, plain);
	phaseII(key, plain);
	
	k = 0;

	int lines = strlen(plain) / strlen(key);

	if (strlen(plain) % strlen(key) != 0)
	{
		lines += 1;
	}

	for (j = 0; j < strlen(key); j++) {
		for (int i = 1; i < lines + 1; i++) {
			if (phaseIIMatrix[i][j] != ' ') {
				encrypted[k] = phaseIIMatrix[i][j];
				k++;
			}			
		}
	}
}

int main()
{
	FILE *f, *g, *h;
	int i;
	char key[1000], plain[1000], cyphered[1000];

	fopen_s(&f, "key.txt", "r");
	fopen_s(&g, "plain.txt", "r");
	fopen_s(&h, "cyphered.txt", "r");
	while (fgets(key, 1000, f) != NULL && fgets(plain, 1000, g) != NULL && fgets(cyphered, 1000, h) != NULL)
	{
		removeSpaces(key);
		removeSpaces(plain);
		removeSpaces(cyphered);
		encryptText(plain, key);
	}	


	for (i = 0; i < strlen(encrypted); i++) {
		printf("%c", encrypted[i]);
	}

	scanf_s("%d", &i);
	return 0;
}

