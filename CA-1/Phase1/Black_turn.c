#include "Black_turn.h"
void Black_turn(char GB[6][6])
{
	int x;
	while (1)
	{
		int check;
		check = scanf("%d", &x);
		int yekan = x % 10;
		int dahgan = x / 10;
		if (check == 1 && x < 67 && ((1 <= yekan) && (yekan <= 6)) && ((1 <= dahgan) && (dahgan <= 6)))
		{
			if (GB[dahgan - 1][yekan - 1] == '.')
			{
				GB[dahgan - 1][yekan - 1] = 'b';
				break;
			}
			else if (GB[dahgan - 1][yekan - 1] == 'w')
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