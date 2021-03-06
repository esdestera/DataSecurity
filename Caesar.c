
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

char* EncryptText(int displacement, char plainText[]) {
	char caesarEncr[100];
	int i, j;

	for (i = 0; i < strlen(plainText); i++) {
		int asciiExpr = (int)plainText[i];
		
		if (asciiExpr >= 65 && asciiExpr <= 90 || asciiExpr >= 97 && asciiExpr <= 122) {
			asciiExpr = asciiExpr + displacement;

			if (asciiExpr > 90 && asciiExpr <= 90 + displacement || asciiExpr > 122 && asciiExpr <= 122 + displacement) {
				asciiExpr = asciiExpr - 26;
			}
		}
		else {
			asciiExpr = plainText[i];
		}

		caesarEncr[i] = (char)asciiExpr;
		printf("%c", caesarEncr[i]);
	}

	return caesarEncr;
}

void DecryptText(int displacement, char encryptedText[]) {
	char plainText[100];
	int i, j;

	for (i = 0; i < strlen(encryptedText); i++) {
		int asciiExpr = (int)encryptedText[i];

		if (asciiExpr >= 65 && asciiExpr <= 90 || asciiExpr >= 97 && asciiExpr <= 122) {
			asciiExpr = asciiExpr - displacement;
						
			if (asciiExpr < 65 && asciiExpr >= 65 - displacement || asciiExpr < 97 && asciiExpr >= 97 - displacement) {
				//printf("%d\n", asciiExpr);
				asciiExpr = asciiExpr + 26;
			}
		}
		else {
			asciiExpr = encryptedText[i];
		}

		plainText[i] = (char)asciiExpr;
		printf("%c", plainText[i]);
	}

}

int main()
{
	int displacement;
	int i, j;
	char expr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	
	printf("Enter the displacement: ");
	scanf_s("%d", &displacement);

	EncryptText(displacement, expr);
	printf("\n");
	DecryptText(displacement, expr);

	scanf_s("%d", &i);
	return 0;
}
