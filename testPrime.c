#include <stdio.h>
#include <stdbool.h>
#include "prime.c"

void main()
{
	char UseCases[13][20] = {"-19", "ads", "3", "7u", "s455", "  234", "sdf3443 345", "  3 1", "44", "53", "23", "-32", "2" };
	bool ExpectedOutputs[] = {false, false, true, false, false, false, false, false, false, true, true, false, true};

	int counter = 0;
	int useCaseCount = 13;
	bool testCaseFailed = false;

	while (counter < useCaseCount)
	{
		if (is_prime(UseCases[counter]) != ExpectedOutputs[counter])
		{
			testCaseFailed = true;
			printf("\n Use case Failed(%s).\n", UseCases[counter]);
		}
		counter++;
	}

	if (!testCaseFailed)
	{
		printf("\nAll test cases passed successfully.\n");
	}
}