// Convert integer to Roman numerals and vice versa.
// Note: numbers range(1 to 3999).

#include <stdio.h>
#include <math.h>
#include <string.h>

char roman[10];
int romanLetters = 0;

void placeRomanDigits(int faceValue, char a, char b, char c)
{
	int counter;

	if (faceValue < 4)
	{
		for (counter = 0; counter < faceValue; counter++)
		{
			roman[romanLetters++] = a;
		}
	}else if(faceValue > 3 && faceValue < 9)
	{
		if (faceValue == 4)
		{
			roman[romanLetters++] = a;
		}
		roman[romanLetters++] = b;
		if (faceValue > 5)
		{
			for (counter = 0; counter < faceValue - 5; counter++)
			{
				roman[romanLetters++] = a;
			}
		}
	}else
	{
		roman[romanLetters++] = a;
		roman[romanLetters++] = c;
	}
}

void convertToRoman(int number)
{
	char sNumber[10];
	sprintf(sNumber, "%d", number);

	int counter, placeValue, faceValue;
	int digits = strlen(sNumber);

	for (counter = 0; counter < digits; counter++)
	{
		faceValue = sNumber[counter] - 48;
		placeValue = pow(10, (digits - counter - 1));

		switch (placeValue)
		{
			case 1 :	placeRomanDigits(faceValue, 'I', 'V', 'X');
						break;

			case 10:	placeRomanDigits(faceValue, 'X', 'L', 'C');
						break;

			case 100:	placeRomanDigits(faceValue, 'C', 'D', 'M');
						break;

			default:	placeRomanDigits(faceValue, 'M', ' ', ' ');
						break;
		}
	}
}

int convertToInteger(char *roman)
{
	int number = 0;
	romanLetters = strlen(roman);
	int counter;

	for (counter = 0; counter < romanLetters; counter++)
	{
		switch(roman[counter])
		{
			case 'I' :	if (roman[counter + 1] != 'V' && roman[counter + 1] != 'X')
						{
							number += 1;
						}else
						{
							number += (roman[++counter] == 'V') ? 4 : 9;
						}
						break;

			case 'V' :  number += 5;
						break;

			case 'X' :	if (roman[counter + 1] != 'L' && roman[counter + 1] != 'C')
						{
							number += 10;
						}else
						{
							number += (roman[++counter] == 'L') ? 40 : 90;
						}
						break;

			case 'L' :	number += 50;
						break;

			case 'C' :	if (roman[counter + 1] != 'D' && roman[counter + 1] != 'M')
						{
							number += 100;
						}else
						{
							number += (roman[++counter] == 'D') ? 400 : 900;
						}
						break;

			case 'D' :	number += 50;
						break;

			case 'M' :	number += 1000;
						break;

			default :	return -1;
		}
	}
	return number;
}

void main()
{
	int choice;
	int number;

	printf("\nConvert");
	printf("\n 1. Decimal to Roman");
	printf("\n 2. Roman to decimal");
	printf("\n\nEnter your choice: ");
	scanf("%d", &choice);

	if (choice == 1)
	{
		do
		{
			printf("\nEnter a number: ");
			scanf("%d", &number);

			if (number < 1 || number > 3999)
			{
				printf("\nSorry %d is out of range, try number between 1 to 3999.\n", number);
			}
		}while (number < 1 || number > 3999);

		convertToRoman(number);
		printf("\n%d in roman number system is %s\n", number, roman);
	}else if (choice == 2)
	{
		printf("\nEnter number in roman romanLetters: ");
		scanf("%s", roman);

		number = convertToInteger(roman);

		if (number != -1)
		{
			printf("\n%s in decimal number system is %d\n", roman, number);
		}else
		{
			printf("\nInvalid roman number!\n");
		}
	}else
	{
		printf("\nInvalid choice!\n");
	}
}