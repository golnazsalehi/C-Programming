#include <stdio.h>
#include<stdlib.h>
#include "Black_turn.h"
#include "White_turn.h"
#include "Black_win_check.h"
#include "White_win_check.h"
#include "board.h"
#include "copy.h"
#include "Turn.h"
int main()
{
	int ans = 0;
	int temp = 0;
	int turn = 0;
	int count = 0;
	char GB[6][6];
	for (int o = 0; o < 6; o++)
	{
		for (int q = 0; q < 6; q++)
		{
			GB[o][q] = '.';
		}
	}
	char gb[6][6];
	board(GB);
	while (1)
	{
		if (turn % 2 == 0)
		{
			printf("Black turn");
			Black_turn(GB);
			system("cls");
			board(GB);
			copy(GB, gb);
			Turn(GB, gb);
			system("cls");
			board(GB);
			copy(GB, gb);
			Black_win_check(GB);
			White_win_check(GB);
			if (Black_win_check(GB) == 1 && White_win_check(GB) == 1)
			{
				printf("you have made a draw!!!shame!");
				//break;
				return 0;
			}
			else if (White_win_check(GB) == 1)
			{
				printf("the  white player has won");
				//break;
				return 0;
			}
			else if (Black_win_check(GB) == 1)
			{
				printf("the black player has won");
				//break;
				return 0;
			}
			count++;
			turn++;
			continue;
		}
		if (turn % 2 == 1)
		{
			printf("White turn");
			White_turn(GB);
			system("cls");
			board(GB);
			copy(GB, gb);
			Turn(GB, gb);
			system("cls");
			board(GB);
			copy(GB, gb);
			White_win_check(GB);
			Black_win_check(GB);
			if (Black_win_check(GB) == 1 && White_win_check(GB) == 1)
			{
				printf("you have made a draw!!!shame!");
				//break;
				return 0;
			}
			else if (White_win_check(GB) == 1)
			{
				printf("the  white player has won");
				//break;
				return 0;
			}
			else if (Black_win_check(GB) == 1)
			{
				printf("the black player has won");
				//break;
				return 0;
			}
			count++;
			turn++;
			continue;
		}
		if (count == 36)
		{
			printf("end of the game!no one has won");
			break;
			return 0;
		}

	}
}
