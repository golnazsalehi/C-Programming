#include "board.h"
void board(char GB[6][6])
{				//GB=Game Board
	int m, n;
	printf("\t");
	for (m = 1; m <= 6; m++)
	{
		if (m == 3)
		{
			printf("%d\t|\t", m);
		}
		else
		{
			printf("%d\t", m);
		}
	}
	printf("\n");
	for (m = 0; m < 6; m++)
	{
		if (m == 3)
		{
			printf("--\t--\t--\t--\t\t--\t--\t--\n\n");
		}
		printf("%d\t", m + 1);
		for (n = 0; n < 6; n++)
		{
			if (n == 3)
			{
				printf("|\t");
			}
			printf("%c\t", GB[m][n]);
		}
		printf("\n\n");
	}
}
