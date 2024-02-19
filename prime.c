// Check whether a number is prime or not.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_prime(char *Number)
{
	int length = strlen(Number);
	int counter = 0;

	while (counter < length)
	{
		if(!isdigit(Number[counter]))
		{
			return false;
		}
		counter++;
	}

	int number = atoi(Number);

	if (number % 2 != 0 && number > 2)
	{
		int divisor = 3;

		while (divisor * divisor <= number)
		{
			if (number % divisor == 0)
			{
				return false;
			}
			divisor += 2;
		}
	}else
	{
		if (number != 2)
		{
			return false;
		}
	}
	return true;
}