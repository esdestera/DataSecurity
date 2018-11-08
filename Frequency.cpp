// Frequency.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numOfKeys 26

struct Pair {
	char key;
	int frequency;
} pairs[numOfKeys];

void createPairs() {
	int letter = 65;
	for (int i = 0; i < numOfKeys; i++) {
		pairs[i].key = (char)letter;
		pairs[i].frequency = 0;
		letter++;
	}
}

void countFrequency(char string[]) {
	int i, j;
	createPairs();
	for (i = 0; i < strlen(string); i++) {
		for (j = 0; j < numOfKeys-1; j++) {
			if (pairs[j].key == string[i] || (int)pairs[j].key == (int)string[i] - 32) {
				pairs[j].frequency++;
				break;
			}
		}
	}
}

int main() {

	FILE *f;
	char c[1000];
	int ret;
	fopen_s(&f, "test.txt", "rt");

	while (fgets(c, 1000, f) != NULL) {
		countFrequency(c);
		for (int ret = 0; ret < 26; ret++) {
			printf("%c - %d\n", pairs[ret].key, pairs[ret].frequency);
		}
	}	

	fclose(f);
	scanf_s("%d", &ret);
	return 0;
}
