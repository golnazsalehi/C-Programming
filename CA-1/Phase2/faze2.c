#include "graphics.h"
#include<stdio.h>
#include "Black_turn.h"
#include "White_turn.h"
#include "Black_win_check.h"
#include "White_win_check.h"
#include "copy.h"
#include "Rotation.h"
#include "board.h"
int main() {
	int ans = 0;
	int temp = 0;
	int turn = 0;
	int count = 0;
	char GB[600][600];
	char gb[600][600];
	initwindow(800, 800, "", 0, 0);
	setfillstyle(1, 1);
	bar(0, 0, 300, 300);
	bar(0, 300, 300, 600);
	bar(300, 0, 600, 300);
	bar(300, 300, 600, 600);
	line(300, 0, 300, 600);
	line(0, 300, 600, 300);
	//setfillstyle(1, 6);
	for (int ah = 0; ah < 6; ah++) {
		for (int oof = 0; oof < 6; oof++) {
			fillellipse(ah * 100 + 50, oof * 100 + 50, 20, 20);
		}
	}

	for (int we = 50; we < 600; we += 100)
	{
		for (int q = 50; q < 600; q += 100)
		{
			GB[we][q] = '.';
		}
	}
	//board(GB);
	while (true)
	{
		if (turn % 2 == 0)
		{
			outtextxy(0, 700, "Black turn");
			Black_turn(GB);
			//system("cls");
			//board(GB);
			copy(GB, gb);
			Rotation(GB, gb);
			system("cls");
			board(GB);
			copy(GB, gb);
			Black_win_check(GB);
			White_win_check(GB);
			if (Black_win_check(GB) == 1 && White_win_check(GB) == 1)
			{
				outtextxy(0, 700, "you have made a draw!!!shame!");
				break;

			}
			else if (White_win_check(GB) == 1)
			{
				outtextxy(0, 700, "the  white player has won");
				break;

			}
			else if (Black_win_check(GB) == 1)
			{
				outtextxy(0, 700, "the black player has won");
				break;

			}
			count++;
			turn++;
			continue;
		}
		if (turn % 2 == 1)
		{
			outtextxy(0, 700, "White turn");
			White_turn(GB);
			//system("cls");
			//board(GB);
			copy(GB, gb);
			Rotation(GB, gb);
			//system("cls");
			board(GB);
			copy(GB, gb);
			White_win_check(GB);
			Black_win_check(GB);
			if (Black_win_check(GB) == 1 && White_win_check(GB) == 1)
			{
				outtextxy(0, 700, "you have made a draw!!!shame!");
				break;

			}
			else if (White_win_check(GB) == 1)
			{
				outtextxy(0, 700, "the  white player has won");
				break;

			}
			else if (Black_win_check(GB) == 1)
			{
				outtextxy(0, 700, "the black player has won");
				break;

			}
			count++;
			turn++;
			continue;
		}
		if (count == 36)
		{
			outtextxy(0, 700, "end of the game!no one has won");
			break;

		}

	}getch();
	closegraph();
	return 0;
}
