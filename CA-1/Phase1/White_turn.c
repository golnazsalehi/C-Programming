#include "White_turn.h"
void White_turn(char GB[6][6])
{
	int x;
	while (1)
	{
		int test;
		test = scanf("%d", &x);
		int ones = x % 10;
		int tens = x / 10;
		if (test == 1 && x < 67 && ((1 <= ones) && (ones <= 6)) && ((1 <= tens) && (tens <= 6)))
		{
			if (GB[tens - 1][ones - 1] == '.')
			{
				GB[tens - 1][ones - 1] = 'w';
				break;
			}
			else if (GB[tens - 1][ones - 1] == 'b')
			{
				printf
				("your opponent has chosen this before,please try again\n");
				continue;
			}
			else
			{
				printf("you have chosen this before,please try again\n");
				continue;
			}
		}
		else
		{
			printf("invalid input,please try again\n");
			getchar();
			continue;
		}
	}
}