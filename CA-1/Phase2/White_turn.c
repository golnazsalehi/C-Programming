#include "graphics.h"
#include "White_turn.h"
void White_turn(char GB[600][600])
{
	int o = 50;
	int gol = 50;
	setcolor(14);
	circle(50, 50, 25);
	while (1)
	{
		int ch;
		ch = getch();
		if (ch == 83 || ch == 115) {
			//S
			if (49 < o < 601 && gol == 550) {
				setcolor(14);
				circle(o, gol, 25);
			}
			else {
				setcolor(14);
				circle(o, gol += 100, 25);
				setcolor(1);
				circle(o, gol -= 100, 25);
				gol += 100;
			}
		}
		else if (ch == 68 || ch == 100) {
			//D
			if (o == 550 && 49 < gol < 601) {
				setcolor(14);
				circle(o, gol, 25);
			}
			else {
				setcolor(14);
				circle(o += 100, gol, 25);
				setcolor(1);
				circle(o -= 100, gol, 25);
				o += 100;
			}
		}
		else if (ch == 87 || ch == 119) {
			//W
			if (49 < o < 601 && gol == 50) {
				setcolor(14);
				circle(o, gol, 25);
			}
			else {
				setcolor(14);
				circle(o, gol -= 100, 25);
				setcolor(1);
				circle(o, gol += 100, 25);
				gol -= 100;
			}
		}
		else if (ch == 65 || ch == 97) {
			//A
			if (o == 50 && 49 < gol < 601) {
				setcolor(14);
				circle(o, gol, 25);
			}
			else {
				setcolor(14);
				circle(o -= 100, gol, 25);
				setcolor(1);
				circle(o += 100, gol, 25);
				o -= 100;
			}
		}
		else if (ch == 70 || ch == 102) {
			//F
			if (GB[o][gol] == '.') {
				GB[o][gol] = 'w';
				setfillstyle(1, 15);
				fillellipse(o, gol, 20, 20);
				break;
			}
			else if (GB[o][gol] == 'w') {
				setcolor(14);
				outtextxy(0, 700, "you have chosen this before\n");
				continue;
			}
			else {
				setcolor(14);
				outtextxy(0, 700, "your opponent has chosen this before\n");
				continue;
			}
		}
	}setcolor(1);
	circle(o, gol, 25);
}