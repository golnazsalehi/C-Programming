#include "Black_turn.h"
#include "graphics.h"
void Black_turn(char GB[600][600])
{

	int x = 50;
	int to = 50;
	setcolor(14);
	circle(50, 50, 25);
	while (1)
	{
		int character;
		character = getch();
		if (character == 83 || character == 115) {
			//S
			if (49 < x < 601 && to == 550) {
				setcolor(14);
				circle(x, to, 25);
			}
			else {
				setcolor(14);
				circle(x, to += 100, 25);
				setcolor(1);
				circle(x, to -= 100, 25);
				to += 100;
			}
		}
		else if (character == 68 || character == 100) {
			//D
			if (x == 550 && 49 < to < 601) {
				setcolor(14);
				circle(x, to, 25);
			}
			else {
				setcolor(14);
				circle(x += 100, to, 25);
				setcolor(1);
				circle(x -= 100, to, 25);
				x += 100;
			}
		}
		else if (character == 87 || character == 119) {
			//W
			if (49 < x < 601 && to == 50) {
				setcolor(14);
				circle(x, to, 25);
			}
			else {
				setcolor(14);
				circle(x, to -= 100, 25);
				setcolor(1);
				circle(x, to += 100, 25);
				to -= 100;
			}
		}
		else if (character == 65 || character == 97) {
			//A
			if (x == 50 && 49 < to < 601) {
				setcolor(14);
				circle(x, to, 25);
			}
			else {
				setcolor(14);
				circle(x -= 100, to, 25);
				setcolor(1);
				circle(x += 100, to, 25);
				x -= 100;
			}
		}
		else if (character == 70 || character == 102) {
			//F
			if (GB[x][to] == '.') {
				GB[x][to] = 'b';
				setfillstyle(1, 0);
				fillellipse(x, to, 20, 20);
				break;
			}
			else if (GB[x][to] == 'b') {
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
	circle(x, to, 25);
}